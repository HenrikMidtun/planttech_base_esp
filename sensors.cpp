#include "sensors.h"
#include "DHT.h"
#include <OneWire.h>
#include <DS18B20.h>
#include "DFRobot_PH.h"
#include "DFRobot_EC.h"
#include <EEPROM.h>

//  SETUP
void sensors_setup()
{
    dht.begin();
    EEPROM.begin(32);
    ph.begin();
    ec.begin();
    if (ds18b20.begin() == false)
    {
        Serial.println("WARNING: Failed to communicate with DS18B20");
    }
}

//  TELEMETRY
float getHumidity()
{
    float h = dht.readHumidity();
    Serial.print("Measured Air Humidity to be: ");
    Serial.println(h, 2);
    return h;
}

float getAirTemperature()
{
    float t = dht.readTemperature();
    Serial.print("Measured Air Temperature to be: ");
    Serial.println(t, 2);
    return t;
}

float getWaterTemperature()
{
    ds18b20.requestTemperatures();
    float w_temp = 0;
    uint32_t timeout = millis();
    while (!ds18b20.isConversionComplete())
    {
        if (millis() - timeout >= 800) // check for timeout, 800ms
        {
            w_temp = -99; //Greide ikke å ta en måling, setter til en vilkårlig urealistisk verdi. ;)
            return w_temp;
        }
    }
    w_temp = ds18b20.getTempC();
    Serial.print("Measured Water Temperature to be: ");
    Serial.println(w_temp, 2);
    return w_temp;
}

// Forbedring, integrere sampling
float getPH()
{
    int potValue = analogRead(PH_PIN);
    float voltage = potValue * 3300 / 4069; // read the voltage as a range from 0-3300
    float temp = getWaterTemperature();
    ph.calibration(voltage, getAirTemperature()); // Calibrating as if the standard pH buffer was at room temperature.
    float phValue = ph.readPH(voltage, temp);     // convert voltage to pH with temperature compensation
    Serial.print("Measured pH to be: ");
    Serial.println(phValue, 2);
    return phValue;
}

float getEC()
{
    int potValue = analogRead(EC_PIN);
    float voltage = potValue * 3300 / 4069; // read the voltage as a range from 0-3300
    float temp = getWaterTemperature();
    ec.calibration(voltage, getAirTemperature()); // Calibrating as if the standard pH buffer was at room temperature.
    float ecValue = ec.readEC(voltage, temp);     // convert voltage to EC with temperature compensation
    Serial.print("Measured EC to be: ");
    Serial.println(ecValue, 2);
    return ecValue;
}