#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define ARR_SIZE 800
const int SIM_SIZE = 15; //alster=15 anders=9

int Sensorwert;

struct data {
  int sensor_wert;
  double latitude;
  double longitude;
  long timestamp;
};


struct coord {
  double latitude;
  double longitude;
};

coord current_point;
int sim_counter = 0;
data zwischenspeicher[ARR_SIZE];
int n_werte = 0;

WiFiClient clientH;



coord sim_points[SIM_SIZE];

void setup() {
  double  lats_alster [] = {53.552055654340215, 53.55441696755527, 53.55881149863554, 53.55922674852853, 53.56711464768213,
                            53.57737136288389, 53.578527788207325, 53.58097660675333, 53.579751728913294, 53.56819744345486, 53.56368639014021,
                            53.5608877532467, 53.557147270524624, 53.555543933197406, 53.55195747370309
                           };
  double lons_alster [] = {9.994610727779422, 9.99084585358996, 9.993975074219113, 9.995674412504847, 10.001156217822066,
                           9.99972881233173, 9.997236923577162, 10.000989369340449, 10.008551318203006, 10.016074453376298, 10.017144966509676,
                           10.012450047667082, 10.002933248369931, 10.000425107829548, 9.994623488424292
                          };


  double  lats_anders [] = {53.58117366176166, 53.57265652190565, 53.57250434992271, 53.57722993909611, 53.57761144145394, 53.57911135934709, 53.580899470883544, 53.58126429629589, 53.58138590167325};
  double lons_anders [] = {9.988657382791484, 9.988604077370479, 9.981851887404869, 9.981865852584392, 9.981479959370978, 9.981798573861264, 9.9817985709493, 9.981790969531358, 9.987541540782095};

  current_point.latitude = lats_alster[0];
  current_point.longitude = lons_alster[0];

  for (int i = 0; i < SIM_SIZE; i++) {
    sim_points[i].latitude = lats_alster[i];
    sim_points[i].longitude = lons_alster[i];
  }

  Serial.begin(115200);                          // Damit unsere Werte später im seriellen Monitor angezeigt werden können, legen wir zuerst die Baudrate 9600 fest.
  WiFi.begin("betahaus2.0", "betahaus10?");
  pinMode( 0 , INPUT);                         // Pin 0 dient nun als Input
  delay(10000); //sensor warmup time

}

void sendServerData() {
  Serial.println("uploading");
  String serverPath = "http://api-pcae.siefke.org/collect/new";
  bool successful = true;
  for (int i = 0; i < n_werte; i++) {
    HTTPClient http;
    http.begin(clientH, serverPath.c_str());
    http.addHeader("Content-Type", "application/json");
    http.setAuthorization("admin", "admin");

    StaticJsonDocument<64> doc;

    doc["timestamp"] = zwischenspeicher[i].timestamp;
    doc["co_value"] = zwischenspeicher[i].sensor_wert;
    doc["longitude"] = zwischenspeicher[i].longitude;
    doc["latitude"] = zwischenspeicher[i].latitude;

    String output;

    serializeJson(doc, output);
    Serial.println(output);

    // Send HTTP GET request
    int httpResponseCode = http.POST(output);
    successful &= (httpResponseCode == 200);
    Serial.print("response code: ");
    Serial.println(httpResponseCode);
    http.end();
  }
  if (successful) {
    n_werte = 0;
  }
}

void print_coord(coord c, String str) {
  Serial.print(str);
  Serial.print(" long: ");
  Serial.println(c.longitude);
  Serial.print(" lat: ");
  Serial.print(c.latitude);
}

void coords_next() {
  coord diff;
  diff.latitude = sim_points[sim_counter].latitude - current_point.latitude;
  diff.longitude = sim_points[sim_counter].longitude - current_point.longitude;

  print_coord(current_point, "current");
  print_coord(sim_points[sim_counter], "dest");
  print_coord(diff, "diff");

  double len = diff.latitude * diff.latitude + diff.longitude * diff.longitude;
  len = sqrt(len);

  double step_dist = 0.00027;

  double scale = step_dist / len;

  Serial.print("next_point n: ");
  Serial.println(sim_counter);

  Serial.print("Len: ");
  Serial.println(len);

  Serial.print("scale: ");
  Serial.println(scale);

  if (scale < 1) {
    current_point.latitude = current_point.latitude + diff.latitude * scale;
    current_point.longitude = current_point.longitude + diff.longitude * scale;
  } else {
    sim_counter++;
    if (sim_counter == SIM_SIZE) {
      sim_counter = 0;
    }
    coords_next();
  }
}

void loop() {

  coords_next();

  if (WiFi.status() == WL_CONNECTED && n_werte > 0) {
    sendServerData();
  }

  if (n_werte < ARR_SIZE) {
    Sensorwert = analogRead(0);              // Zuerst wird der Wert am Pin A0 ausgelesen...
    zwischenspeicher[n_werte].sensor_wert = Sensorwert;
    zwischenspeicher[n_werte].timestamp = 0;
    zwischenspeicher[n_werte].latitude = current_point.latitude;
    zwischenspeicher[n_werte].longitude = current_point.longitude;
    n_werte++;

    Serial.print("Der erfasste Wert lautet : ");
    Serial.print(n_werte);
    Serial.print(" - ");
    Serial.println(Sensorwert, DEC);         //... und anschließend im seriellen Monitor als Dezimalzahl ausgegeben.
    Serial.println();
  }


  delay(500);
}
