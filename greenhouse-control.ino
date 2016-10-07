
#include <Wire.h>  // Comes with Arduino IDE

//#include <OneWire.h>


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

//Pins for HC-SR04 ultrasonic distance sensor
const int pingPin = 7; //Trigger Pin
const int pongPin = 8; //Echo Pin


const int wateringPumpPin = 4;
const int fanPin = 3;


const int humidityGroundSensorPin = A0;
const int humidityAirSensorPin = A1;
const int brightnessOutsideSensorPin = A2;
const int brightnessInsideSensorPin = A3;
const int tempOutsideSensorPin = A6;
const int tempInsideSensorPin = A7;

const int menuSwitchButton = 12; //button used to switch through the menu/infoscreen on the LCD, note: a pullup resistor is required


//define global variables
int lcd_infoscreen = 2;
int maxTemp_celsius = 50; //when maxTemp is reached, fan will be turned on

long distance_cm;
long waterlevel_cm;
    
long humidityGround_percent;

long humidityAir_percent;

long brightnessOutside_percent;
long brightnessInside_percent;

long tempInside_celsius;
long tempOutside_celsius;

unsigned long lcdLastUpdateMillis = 0;        // will store last time the lcd was updated
const long lcdUpdateInterval = 2000;           // interval at which to update the lcd screen
unsigned long sensorsLastUpdateMillis = 0;    // will store last time the sensor values were updated
const long sensorsUpdateInterval = 100;      // interval at which to update the sensor values

unsigned long currentMillis = 0;              //used to buffer current time in milliseconds


int buttonState = 0;              // current state of the menuSwitchButton
int lastButtonState = 0;          // previous state of the menuSwitchButton

void setup()
{
  Serial.begin(9600);
  
 
  pinMode(pongPin, INPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(wateringPumpPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  pinMode(menuSwitchButton, INPUT);
  
  
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
    if(/*humidityGround_percent >= 80 ||*/ humidityAir_percent >=70 || (tempInside_celsius >= maxTemp_celsius && tempInside_celsius<=tempOutside_celsius)){
      digitalWrite(fanPin,HIGH);
    }else{
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

void doSensorReadings(){
  
  distance_cm = getWaterDistance(pingPin,pongPin); //get distance of water to sensor HC-SR04
  waterlevel_cm = map(distance_cm,10,30,20,0);  //calculate water level
    
  humidityGround_percent = map(analogRead(humidityGroundSensorPin),140,1023,100,0); //get humidity of ground 
    
  humidityAir_percent = map(analogRead(humidityAirSensorPin),140,1023,100,0); //replace this dummy reading with DHTxx sensor reading later
    
  brightnessOutside_percent = map(analogRead(brightnessOutsideSensorPin),0,1023,0,100); //get brightness from LDR
  brightnessInside_percent = map(analogRead(brightnessInsideSensorPin),0,1023,0,100); //get brightness from LDR

  tempInside_celsius = map(analogRead(tempInsideSensorPin),0,307,0,150); //get temperature in degree celsius from LM35 sensor, which gives 0-1,5V for 0-150degC
  tempOutside_celsius = map(analogRead(tempOutsideSensorPin),0,307,0,150); //get temperature in degree celsius from LM35 sensor, which gives 0-1,5V for 0-150degC

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
         lcd.print("bright.outs.:");
         lcd.print(brightnessOutside_percent);
         lcd.print("%");
     
         
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
