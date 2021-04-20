#ifndef SENSOR_h
#define SENSOR_h
#include "Arduino.h"

//  SENSOR PINS
// DHT Air Temperature and Humidity sensor
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// SEN0161 pH meter
#define PH_PIN 36
DFRobot_PH ph;

// DFR0300 EC meter
#define EC_PIN 34
DFRobot_EC ec;

// DS18b20 Waterproof Temperature sensor
#define ONE_WIRE_BUS 16
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 ds18b20(&oneWire);

//  SETUP
void sensors_setup();

//  TELEMETRY
float getAirTemperature();
float getHumidity();
float getPH();
float getEC();
float getWaterTemperature();

#endif