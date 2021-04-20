#include "comms.h"
#include <ArduinoJson.h>
#include "sensors.h"

//  VARS
/*
    VARS
  The variables 'name' and 'measurement' are general tags for the device.
  They are used for InfluxDB
  The name of the device, e.g. 'weather-station'
  The type of measurements, e.g. 'outside-weather-data'
*/
const String name = "chili-monitor";
const String measurement = "chili-data";

StaticJsonDocument<512> doc;

void setup() {
  Serial.begin(115200);
  unsigned long time_reference = millis();
  while (!Serial && millis() - time_reference < 5000)
  {
    ;
  }
  comms_setup();
  
  sensors_setup();
}

void loop() {
  comms_loop();

  /*
      TAGS
  */
  doc["tags"]["room"] = "chilirommet";
  doc["tags"]["plant"] = "chili";
  doc["tags"]["grow-system"] = "dwc";
  doc["tags"]["tank"] = "reservoir";
  /*
      FIELDS
  */
  doc["fields"]["dfr-ec"] = getEC();
  doc["fields"]["dht-temperatur"] = getAirTemperature();
  doc["fields"]["dht-fuktighet"] = getHumidity();
  doc["fields"]["ds18-temperatur"] = getWaterTemperature();
  doc["fields"]["sen-ph"] = getPH();

  /*
      TIMESTAMP
  */
  doc["timestamp"] = getTimestamp();

  /*
      SEND (or print)
  */
  sendMessage();
  delay(180000);
}

void printMessage(){
  serializeJson(doc,Serial);
  Serial.println();
}

// Sends the data to the broker, and resets the document for new fields.
void sendMessage(){
  char* sub_topic = "readings";
  char payload[300];
  serializeJson(doc,payload);
  resetDocument();
  comms_publish(sub_topic, payload);
}

/*
    Resets the document.
    Auto generates with the set name and measurement.
    Also inserts empty collections for tags and fields.
*/
void resetDocument(){
  doc.clear();
  doc["name"] = name;
  doc["measurement"] = measurement;
  JsonObject tags = doc.createNestedObject("tags");
  JsonObject fields = doc.createNestedObject("fields");
}