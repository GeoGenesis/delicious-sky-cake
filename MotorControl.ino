/*
 * Code written by GEORGE GOODSELL
 * Student ID: 120015759
 * City University, 2016
 * THESIS WORK
 */
 
#include <Servo.h>

Servo servoMain; // Servo Define

int SERIAL_REFRESH_RATE = 9600;
int PIN = 10; 
//int SERIAL_INPUT = 0;

//====================== MAIN FUNCTIONS =============================\\

void setup()
{
   servoMain.attach(PIN); // servo on digital pin 10
   Serial.begin(SERIAL_REFRESH_RATE);
}

void loop()
{
  servoDiag();
}

//====================== ADDITIONAL FUNCTIONS =============================\\

// Servo Diagnostic Function - 
// Checks the Servo for mechanical failure: uses servoWrite function to rotate Servo Head then pauses.
// Variable D used for delay between angle changes in milliseconds
// Function can also be used to assess maximum servo realignment speed by lowering variable D

void servoDiag() {
   
   int D = 250;          // Delay between change (milliseconds)

   Serial.println("==================================================");
   Serial.print("TEST SPEED : ");
   Serial.print(D);
   Serial.println(" milliseconds");

   for(int i = 0; i <= 180; i = i+45){
      servoWrite(i, D);
    }
   
//   OLD SERVO TEST
//   servoWrite(0, D);      // Turn Servo Left to 0 degrees        
//   servoWrite(45, D);     // Servo to 45
//   servoWrite(90, D);     // Servo to 90
//   servoWrite(135, D);    // Servo to 135
//   servoWrite(180, D);    // Servo to 180

   servoWrite(90, 5000);  // Servo to midpoint and long pause

}

// Servo Run Function -
// Sends signal to Servo: Makes use of <Servo.h> Library, sends a signal to Servo to change its angle.
// Input variables for Requested Angle (int A) and Delay between change (int D)
// Outputs current angle to Serial Monitor

void servoWrite(int A, int D) { 
  servoMain.write(A);        // Rotate Servo to specified angle
  serialOut(servoMain.read());   // Print Servo angle to Serial Monitor
  delay(D);                   // Wait 1 second (1000 Milliseconds)
}

// Serial Handler -
// Message Output: Outputs angle to Serial Monitor with formatting
// Input variable of current angle

void serialOut(int angleMeasure) {
  Serial.print("Current Angle:    ");
  Serial.println(angleMeasure);
  }

//void serialIn() {
//
//  if(Serial.available() > 0) {
//      SERIAL_INPUT = Serial.read();
//      Serial.print("Message Recieved: ");
//      Serial.print(SERIAL_INPUT);
//    }
//}
