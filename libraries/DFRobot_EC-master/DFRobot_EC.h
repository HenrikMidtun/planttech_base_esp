/*
 * file DFRobot_EC.h * @ https://github.com/DFRobot/DFRobot_EC
 *
 * Arduino library for Gravity: Analog Electrical Conductivity Sensor / Meter Kit V2 (K=1), SKU: DFR0300
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2018
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.01
 * date  2018-06
 */

#ifndef _DFROBOT_EC_H_
#define _DFROBOT_EC_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define RAWEC_1413_LOW 0.70
#define RAWEC_1413_HIGH 1.80
#define RAWEC_1288_LOW 8
#define RAWEC_1288_HIGH 16.8

#define ReceivedBufferLength 10  //length of the Serial CMD buffer

class DFRobot_EC
{
public:
    DFRobot_EC();
    ~DFRobot_EC();
    void    calibration(float voltage, float temperature,char* cmd);        //calibration by Serial CMD
    void    calibration(float voltage, float temperature);                  //calibration by Serial CMD
    float   readEC(float voltage, float temperature);                       // voltage to EC value, with temperature compensation
    void    begin();                                                        //initialization

private:
    float  _ecvalue;
    float  _kvalue;
    float  _kvalueLow;
    float  _kvalueHigh;
    float  _voltage;
    float  _temperature;
    float  _rawEC;

    char   _cmdReceivedBuffer[ReceivedBufferLength];  //store the Serial CMD
    byte   _cmdReceivedBufferIndex;

private:
    boolean cmdSerialDataAvailable();
    void    ecCalibration(byte mode); // calibration process, wirte key parameters to EEPROM
    byte    cmdParse(const char* cmd);
    byte    cmdParse();
};

#endif
