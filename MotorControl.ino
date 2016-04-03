/*
 * Code written by GEORGE GOODSELL
 * Student ID: 120015759
 * City University, 2016
 * THESIS WORK
 */

#include <Servo.h>
#include <Wire.h>

Servo servoMain; // Servo Define

int SERIAL_REFRESH_RATE = 9600;
int PIN = 10; 

//====================== MAIN FUNCTIONS =============================\\

void setup()
{
   servoMain.attach(PIN); // servo on digital pin 10
   Serial.begin(SERIAL_REFRESH_RATE);
}

void loop()
{
  servoDiag();
//  wiper(0);
}

//====================== ADDITIONAL FUNCTIONS =============================\\

void servoDiag() {
   int D = 1000;
   
   servoWrite(0, D);      // Turn Servo Left to 0 degrees        
   servoWrite(45, D);     // Servo to 45
   servoWrite(90, D);     // Servo to 90
   servoWrite(135, D);    // Servo to 135
   servoWrite(180, D);    // Servo to 180
   servoWrite(90, 5000);  // Servo to midpoint and long pause

}

void servoWrite(int angle, int Delay) { 
  servoMain.write(angle);        // Rotate Servo to specified angle
  serialOut(servoMain.read());   // Print Servo angle to Serial Monitor
  delay(Delay);                   // Wait 1 second (1000 Milliseconds)
}

void serialOut(int angleMeasure) {
  Serial.print("Current Angle:    ");
  Serial.println(angleMeasure);
  }
