
#include <Wire.h>  // Comes with Arduino IDE
#include "DHT.h"  
#include <OneWire.h>


// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x3F for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
// I2C pins are A4 (sda) and A5 (scl)
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
/*-----( Declare Variables )-----*/

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//Pin for the DHT22 sensor
const int dhtPin = 9;
//Initialise DHT sensor
DHT dht(dhtPin, DHTTYPE);

//Pin for the DS sensor (used for ground temperature)
const int temperatureGroundSensorPin = 10;
OneWire  ds(temperatureGroundSensorPin);  // on pin 10 (a pullup resistor is necessary)


//Pins for HC-SR04 ultrasonic distance sensor
const int pingPin = 7; //Trigger Pin
const int pongPin = 8; //Echo Pin

const int wateringPumpPin = 4;
const int fanPin = 3;

const int windowOpenPin = 5;
const int windowClosePin = 6;

const int humidityGroundSensorPin = A0;
const int humidityAirSensorPin = A1;
const int brightnessOutsideSensorPin = A2;
const int brightnessInsideSensorPin = A3;
const int tempOutsideSensorPin = A6;
const int tempInsideSensorPin = A7;

const int menuSwitchButton = 12; //button used to switch through the menu/infoscreen on the LCD, note: a pullup resistor is required


//define global variables
int lcd_infoscreen = 2;

long distance_cm;
long waterlevel_cm;
    

//Brightness
long brightnessOutside_percent;
long brightnessInside_percent;

//Temperature control
long tempInside_celsius;
long tempOutside_celsius;
long tempGround_celsius;

int maxTemp_celsius = 40; //when maxTemp is reached, fan will be turned on
int fanHysteresis_celsius = 4; //describes how much lower than maxTemp_celsius the actual temperature has to be so that fans will be turned off again

//int minTemp_celsius = 5; //when minTemp is reached, heating will be turned on (radiators or whatever)
//int heatingHysteresis_ceslsius = 4; //describes how much higher than minTemp_celsius the actual temperature has to be so that heating will be turned off again


//Humidity control
long humidityGround_percent;
long humidityAir_percent;

int maxHumidityAir_percent = 60;
int humidityAirThreshold = 10;

unsigned long lcdLastUpdateMillis = 0;        // will store last time the lcd was updated
const long lcdUpdateInterval = 2000;           // interval at which to update the lcd screen
unsigned long sensorsLastUpdateMillis = 0;    // will store last time the sensor values were updated
const long sensorsUpdateInterval = 500;      // interval at which to update the sensor values

unsigned long currentMillis = 0;              //used to buffer current time in milliseconds


int buttonState = 0;              // current state of the menuSwitchButton
int lastButtonState = 0;          // previous state of the menuSwitchButton

void setup()
{
  Serial.begin(19200);
  
 
  pinMode(pongPin, INPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(wateringPumpPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  pinMode(menuSwitchButton, INPUT);

  dht.begin();
  
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(50);
    lcd.noBacklight();
    delay(50);
  }
  lcd.backlight(); // finish with backlight on  

}


void loop()
{

    //take care of sensor readings
    currentMillis = millis();
    if (currentMillis - sensorsLastUpdateMillis >= sensorsUpdateInterval) {
      // save the last time the sensor values were updated
      sensorsLastUpdateMillis = currentMillis;
      //read from sensors and convert units
      doSensorReadings();
    } 
    
    //Control Watering Pump
    if((waterlevel_cm >= 10) && (humidityGround_percent <= 20)){
      digitalWrite(wateringPumpPin,HIGH);
    }else{
      digitalWrite(wateringPumpPin,LOW);
    }

    //Control Fan
    //Turn ON if: 
    // humidity is too high
    // OR
    // temperature inside is too high AND outside its lower than inside (thus ventilating will cool inside)

    //Turn OFF if:
    // temperature inside low enough OR temperature outside higher than inside (thus ventilating is not cooling anymore)
    // AND
    // humidity low enough
    
    if(humidityAir_percent >= maxHumidityAir_percent || (tempInside_celsius >= maxTemp_celsius && tempInside_celsius>=tempOutside_celsius)){
      digitalWrite(fanPin,HIGH);
    }else if(((tempInside_celsius  <= maxTemp_celsius - fanHysteresis_celsius ) || tempInside_celsius <= tempOutside_celsius) && humidityAir_percent <= maxHumidityAir_percent - humidityAirThreshold){
      digitalWrite(fanPin,LOW);
    }

    
    
    //take care of LCD output
    currentMillis = millis();
    if (currentMillis - lcdLastUpdateMillis >= lcdUpdateInterval) {
      // save the last time the lcd was updates
      lcdLastUpdateMillis = currentMillis;
      //call LCD output function
      printLcdInfoscreen();
    } 

   //handle menuSwitchButton (to switch through the menu/infoscreen)
   buttonState = digitalRead(menuSwitchButton);
   //check if state has changed
   if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      
      } else {
        //hop to next page or reset to first page
        if(lcd_infoscreen<2){
          lcd_infoscreen++;
        }else{
          lcd_infoscreen = 1;
        }
        //call LCD output function immediately
        printLcdInfoscreen();
    }
    delay(50);
  }
  lastButtonState = buttonState;
   
  delay(1); 
    
}/* --(end main loop )-- */


//function definitions

long getWaterDistance(int pingPin, int pongPin){

    //returns the distance in cm of watersurface to the ultrasonic sensor 
    
    long duration, distance_cm;

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    //give HIGH pulse
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    //kill HIGH pulse
    digitalWrite(pingPin, LOW);
  
    
    // sensor returns a HIGH pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    
    duration = pulseIn(pongPin, HIGH);

    distance_cm =microsecondsToCentimeters(duration);
    
    return distance_cm;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or ~29.4 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29.4 / 2;
}

float getDSTemperature(){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  //Addresses: DS18B20 TO-92 {0x10,0x14,0xBA,0x8D,0x02,0x08,0x00,0xF3}
  //leave empty to use ds.search to find the address
  byte addr[8] = {0,0,0,0,0,0,0,0};//={0x10,0x14,0xBA,0x8D,0x02,0x08,0x00,0xF3};
  float celsius = 0;
  
  if(addr[0]==0){
    if ( !ds.search(addr)) {
      //Serial.println("No more One Wire addresses.");
      //Serial.println();
      ds.reset_search();
      //delay(250);
      return;
    }
  }
  
  //Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    //Serial.write(' ');
    //Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.print("CRC of OneWire address is not valid, should be:");
      Serial.println(OneWire::crc8(addr, 7),HEX);
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      //Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      //Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      //Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  //delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  //Serial.print("  Data = ");
  //Serial.print(present, HEX);
  //Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    //Serial.print(data[i], HEX);
    //Serial.print(" ");
  }
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  //fahrenheit = celsius * 1.8 + 32.0;
  //Serial.print("  Temperature = ");
  //Serial.print(celsius);
  //Serial.print(" Celsius, ");
  return celsius;
}

void doSensorReadings(){
  
  distance_cm = getWaterDistance(pingPin,pongPin); //get distance of water to sensor HC-SR04
  waterlevel_cm = map(distance_cm,10,30,20,0);  //calculate water level
    
  humidityGround_percent = map(analogRead(humidityGroundSensorPin),140,1023,100,0); //get humidity of ground 
    
  humidityAir_percent = dht.readHumidity(); 
  
  brightnessOutside_percent = map(analogRead(brightnessOutsideSensorPin),0,1023,0,100); //get brightness from LDR
  brightnessInside_percent = map(analogRead(brightnessInsideSensorPin),0,1023,0,100); //get brightness from LDR

  tempInside_celsius = dht.readTemperature(); //get temperature in degree celsius from LM35 sensor, which gives 0-1,5V for 0-150degC
  tempOutside_celsius = map(analogRead(tempOutsideSensorPin),0,307,0,150); //get temperature in degree celsius from LM35 sensor, which gives 0-1,5V for 0-150degC
  tempGround_celsius = getDSTemperature();
}

void printLcdInfoscreen(){
  switch(lcd_infoscreen){
        case 1:
          //print waterlevel
          lcd.setCursor(0,0);
          lcd.print("                    ");
          lcd.setCursor(0,0);
          lcd.print("Waterlevel is:");
          lcd.print(waterlevel_cm);
          lcd.print("cm");
      
          //print ground humidity
          lcd.setCursor(0,1);
          lcd.print("                    ");
          lcd.setCursor(0,1);
          lcd.print("GND hum. is:");
          lcd.print(humidityGround_percent);
          lcd.print("%");
      
          //print ground humidity
          lcd.setCursor(0,2);
          lcd.print("                    ");
          lcd.setCursor(0,2);
          lcd.print("Air hum. is:");
          lcd.print(humidityAir_percent);
          lcd.print("%/");
          lcd.print(maxHumidityAir_percent);
          lcd.print("%");
      
          //print brightness outside
          lcd.setCursor(0,3);
          lcd.print("                    ");
          lcd.setCursor(0,3);
          lcd.print("bright.outs.:");
          lcd.print(brightnessOutside_percent);
          lcd.print("%");

          //print page number to bottom right corner
          lcd.setCursor(19,3);
          lcd.print(lcd_infoscreen);
  
       break;
  
       case 2:
         //print some other info to screen
         
         lcd.setCursor(0,0);
         lcd.print("                    ");
         lcd.setCursor(0,0);
         lcd.print("bright.ins.:");
         lcd.print(brightnessInside_percent);
         lcd.print("%");
     
         
         
         lcd.setCursor(0,1);
         lcd.print("                    ");
         lcd.setCursor(0,1);
         lcd.print("T.g.:");
         lcd.print(tempGround_celsius);
         lcd.print("degC");
     
         
         lcd.setCursor(0,2);
         lcd.print("                    ");
         lcd.setCursor(0,2);
         lcd.print("T.o.:");
         lcd.print(tempOutside_celsius);
         lcd.print("degC");
     
         
         lcd.setCursor(0,3);
         lcd.print("                    ");
         lcd.setCursor(0,3);
         lcd.print("T.i.:");
         lcd.print(tempInside_celsius);
         lcd.print("degC/");
         lcd.print(maxTemp_celsius);
         lcd.print("degC");
         
         //print page number to bottom right corner
         lcd.setCursor(19,3);
         lcd.print(lcd_infoscreen);
       break;
       
       
       default:
         lcd.clear();
         //print page number to bottom right corner
         lcd.setCursor(0,0);
         lcd.print("value of lcd_infoscreen");
         lcd.setCursor(0,1);
         lcd.print("is out of bounds");
         
         lcd.setCursor(19,3);
         lcd.print(lcd_infoscreen);
       break;
       
    }
}

//end function definitions
