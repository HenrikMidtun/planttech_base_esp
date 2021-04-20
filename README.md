# planttech_base_esp
Example code and utility files for Plant Tech.

The program is written for the ESP32 in mind. 
The libraries for the EC and PH sensors are included because these have had changes made to fit the ESP32's 3V logic.
The libraries for EC and PH are made by DFRobot (https://github.com/DFRobot) and the modifications are inspired by GreenPonik (https://github.com/GreenPonik)

The following steps are required to install the program onto a device.
1. Get program to flash the device (Arduino IDE)
2. Getting the Arduino Core for ESP32 (https://github.com/espressif/arduino-esp32)
3. Install the missing libraries

There are fields in the code that the user must modify.
These include fields that are required for communication and data gathering.
