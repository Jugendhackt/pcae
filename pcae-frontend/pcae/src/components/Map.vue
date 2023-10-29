<script setup>
import {onMounted} from 'vue'
import {dataCOColor, fetchDataPoints} from "@/scripts/mapStuff";

var map_annotations = []

onMounted(() => {
  var map = L.map('map').setView([53.563859881246564, 9.962454321792514], 13);
  L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    maxZoom: 19,
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
  }).addTo(map);

  let intervalId = window.setInterval(function(){
    fetchDataPoints().then(dataPoints => {
      map_annotations.forEach(anno => map.removeLayer(anno))
      console.log(dataPoints)
      map_annotations = dataPoints.map(dP => {
        return L.circle([dP.latitude, dP.longitude], {
          color: "none",
          fillColor: dataCOColor(dP.co_value),
          fillOpacity: 0.5,
          radius: 25
        }).addTo(map)
      })
    }).catch(e => console.log(e))
  }, 5000);

})
</script>

<template>
  <div id="map"></div>
</template>

<script>

</script>

<style scoped>
  #map {
    width:100vw;
    height: 100vh;
  }

</style>