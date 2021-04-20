
#include "comms.h"

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>

// Networking and MQTT
IPAddress localIP;
static WiFiClient espClient;
static PubSubClient client(espClient);
int status = WL_IDLE_STATUS;     // the starting Wifi radio's status

// Timestamp
#define NTP_ADDRESS  "europe.pool.ntp.org"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS);


void comms_setup() {
  delay(10);
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, pswd);

  int status = WL_IDLE_STATUS;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Try to connect.");
    delay(500);
  }
  status = WL_CONNECTED;
  Serial.println("Wifi Connected");
  localIP = WiFi.localIP();
  client.setServer(mqtt_server, 1883);
  timeClient.begin();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Decide to use username and password
    bool user_pass_exists = true;
    if(username == "" || password == ""){
      user_pass_exists = false;
    }
    if(user_pass_exists){
      if (client.connect(client_id, username, password)) {    
       break;
      }
    } 
    else{
      if(client.connect(client_id)){
        break;
      }
    }
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.print(" wifi=");
    Serial.print(WiFi.status());
    Serial.println(" retrying in 5 seconds");
    delay(5000);
  }
  Serial.println("connected");
  Serial.print("cliented connected = ");
  Serial.println(client.connected());
}


void comms_publish(const char* sub_topic, const char* msg_payload){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  std::string fullPath = stub_topic;
  fullPath += sub_topic;
  const char *msg_topic = fullPath.c_str();
  client.publish(msg_topic, msg_payload, true);
}

void comms_loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

unsigned long getTimestamp(){
  while(!timeClient.update()){
    ;;
  }
  return timeClient.getEpochTime();
}
