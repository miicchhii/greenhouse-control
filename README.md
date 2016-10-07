# greenhouse-control
A small greenhouse control based on an Arduino Nano Board (or compatible)

## Hardware
This is the setup for which the standard code is written,
it can easily be changed though.

###Sensor list:

waterlevel - HC-SR04 ultrasonic sensor - returns a pulse with the length of trigger to echo delay

humidity ground - a simple sensor made from mechanical pen blackleads and a single BC547

*humidity air - DHT11 or DHT22 probably - a 10k pot is being used instead for testing

brightness inside - LDR (light dependent resistor) and a normal resistor as voltage divider

brightness outside - LDR (light dependent resistor) and a normal resistor as voltage divider

*temperature outside - LM35DZ most likely - outputs 0-1.5V for 0-150°C pretty much linear

*temperature inside - LM35 DZ as well

*temperature ground - DS18B20 in a stainless steel hull - uses the One-Wire Protocol



Sensors prefixed with an asterix (*) are not yet implemented completly or at all.



###Actuators:

I use a single ULN2803 to control the 12V fans and pumps,
although more might be added later on.


Output pin mapping: 

const int wateringPumpPin = 4;

const int fanPin = 3;


LCD-Screen:

4x20 I²C LCD Screen, character based

// I2C pins are A4 (sda) and A5 (scl)



## Configuration

###Constants
####int maxTemp_celsius
Temperature (in °Celsius) above which the fan will be turned on to force ventilation through the greenhouse, thus cooling.
default=50°C

####long lcdUpdateInterval
Holds the interval in ms (milliseconds) at which the LCD should be updated. 
default=2000ms

####long sensorUpdateInterval
Holds the interval in ms (milliseconds) at which the sensor values should be retrieved and saved to the corresponding variables.
default=100ms

## Functions

####long microsecondsToCentimeters(long microseconds)
Converts a ms (milliseconds) value into a corresponding distance in cm (centimeter)

Used with the ultrasonic distance sensor.

####void doSensorReadings()
Handles all the sensor readings and conversions.

No return, since it writes directly to global variables ;-)

####void printLcdInfoscreen()
Print the infoscreen to the LCD.

Uses a switch/case (lcd_infoscreen) to display different pages of information

####long getWaterDistance(int pingPin, int pongPin)
pingPin is the pin used to trigger the measurement

pongPin is the pin used to read the echo from the sensor

returns the distance in cm (centimeter) of the sensor to the nearest detected object

