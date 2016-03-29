/*
 * Code written by GEORGE GOODSELL
 * Student ID: 120015759
 * City University, 2016
 * THESIS WORK
 */

#include <Servo.h>
#include <Wire.h>

#define accel_module (0x53)

Servo servoMain; // Servo Define

int SERIAL_REFRESH_RATE = 9600;
int PIN = 10; 

byte accelValues[6];
char output[512];

//====================== MAIN FUNCTIONS =============================\\

void setup()
{
  
   servoMain.attach(PIN); // servo on digital pin 10
   Wire.begin();
   Serial.begin(SERIAL_REFRESH_RATE);
   
   wireSetup();
   
}


void loop()
{
  servoTest();
//  wiper(0);
}

//====================== ADDITIONAL FUNCTIONS =============================\\

void servoTest() {
   servoMain.write(45);  // Turn Servo Left to 45 degrees
   delay(1000);          // Wait 1 second
   servoMain.write(0);   // Turn Servo Left to 0 degrees
   delay(1000);          // Wait 1 second
   servoMain.write(90);  // Turn Servo back to center position (90 degrees)
   delay(1000);          // Wait 1 second
   servoMain.write(135); // Turn Servo Right to 135 degrees
   delay(1000);          // Wait 1 second
   servoMain.write(180); // Turn Servo Right to 180 degrees
   delay(1000);          // Wait 1 second
   servoMain.write(90);  // Turn Servo back to center position (90 degrees)
   delay(5000);          // Wait 5 seconds

   wireLoop();
  
  }


  void wiper(int x) {

    String partA = String("Angle: ");
    String partB = String(x);
    String output (partA + partB);
    
    Serial.println(partA); // output to serial monitor
    
    servoMain.write(x); // Set to angle x
    Serial.println(partB);
    delay(500);

    x = x+180;
    
    servoMain.write(x);
    Serial.println(output);
    delay(500);
    
    servoMain.write(x-180);
    delay(500);
    }

void serialHandler() {
  }

void wireSetup() {
  
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D); //Write to Register
  Wire.write(0); //Clear Register
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  
  }

void wireLoop() {
  
  int xyzReg = 0x32;
  int x, y, z;

  Wire.beginTransmission(accel_module);
  Wire.write(xyzReg);
  Wire.endTransmission();
  
  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module, 6);
  
  int i = 0;
  while(Wire.available()){
    accelValues[i] = Wire.read();
    i++;
    }
    
  Wire.endTransmission();
  
   x = (( (int)accelValues[1] ) << 8) | accelValues[0];
   y = (( (int)accelValues[3] ) << 8) | accelValues[2];
   z = (( (int)accelValues[5] ) << 8) | accelValues[4];
   
  sprintf(output, "%d %d %d", x, y, z);
  Serial.print(output);
  Serial.write(10);
  
  delay(1000);

  }
