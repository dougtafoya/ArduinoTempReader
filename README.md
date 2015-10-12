# ArduinoTempReader
Simple Arduino program for reading the temperature using a thermistor. Includes Win32 app for accessing the values output by the Arduino.

Using a thermistor and a 10k resistor you can read the temperature using an Arduino and then using a simple Win32 console app you can connect to it and read the values over the serial connection. I used this set up to connect the thermistor to the Arduino:

 (Ground) ---- (10k-Resistor) -------|------- (Thermistor) ---- (+5v)
                                     |
                                Arduino analog pin 0

This uses the 10k resistor as a voltage divider so you can read the resistance of the thermistor. Once you have the value you use the Steinhart–Hart equation to calculate the temperature. Don't worry, I don't really understand that one very well either but it's a well known equation for computing the resistance of a semiconductor at different temperates.

There are much more complicated versions that give you greater control and more accurate readings but I tested this against a proper thermostat and the readings were more or less the same.
