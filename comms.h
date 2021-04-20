#ifndef COMMS_h
#define COMMS_h
#include "Arduino.h"

// Update these with values suitable for your network.
//  WiFi
static const char *ssid = "wifi name";
static const char *pswd = "wifi password";

//  MQTT
static const char *mqtt_server = "test.mosquitto.org";
static const char *client_id = "ESP_chili"; // NB! Should be unique for all clients
static const char *username = "";           // Leave blank for no authentification to Mosquitto Broker
static const char *password = "";
static const char *stub_topic = "device/";

void comms_setup();
void comms_publish(const char *topic, const char *msg);
void comms_loop();
unsigned long getTimestamp();

#endif