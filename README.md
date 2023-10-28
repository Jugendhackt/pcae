# pcae

## Backend

### Endpoints

#### POST: collect/new

body:
```json
{
  "timestamp": "Timestamp",
  "co_value": "Int",
  "longitude": "Double",
  "latitude": "Double"
}
```

response:

String (success)

#### GET: retreive/all

no-args

response:

```json
[
  {
    "id": "Long",
    "longitude": "Double",
    "latitude": "Double",
    "co_value": "Int",
    "timestamp": "Timestamp"
  }
]
```

#### POST: retreive/between

body:

```json
{
  "minLat": "Double",
  "minLon": "Double",
  "maxLat": "Double",
  "maxLon": "Double"
}

response:

```json
[
  {
    "id": "Long",
    "longitude": "Double",
    "latitude": "Double",
    "co_value": "Int",
    "timestamp": "Timestamp"
  }
]
```

