/*
   Code written by GEORGE GOODSELL
   Student ID: 120015759
   City University, 2016
   THESIS WORK
*/

#include <Servo.h>

Servo servoMain; // Servo Define

int SERIAL_REFRESH_RATE = 9600;
int PIN = 10;

// Set angle - system will work to adjust itself to this angle
// DEFAULT: 90
int BASE_ANGLE = 90;

// Degrees of Tolerance - how many degrees rig can be rotated before activating system
// DEFAULT: 5
int TOLERANCE = 5;

//==================== SETUP + LOOP FUNCTIONS =========================\\

void setup()
{
  servoMain.attach(PIN); // servo on digital pin 10
  Serial.begin(SERIAL_REFRESH_RATE);
}

void loop()
{
  // Value is fed to correct function
  correct(random(0, 180)); 
  delay(3000);
  //servoDiag();
}

//====================== PRIMARY FUNCTIONS =============================\\

// Correction Function -
// Uses the adjust function to solve for correction angle, sends signal to Servo to fix.
// Input is the angle from the Accelerometer
//============================

void correct(int accelAngle) {

  // Update Speed - How quickly the angle is adjusted (refresh rate) in Milliseconds
  // DEFAULT: 1000
  int refreshRate = 1000;

  // Check to see if value needs to be adjusted (outside of accepted boundries)
  if (accelAngle < BASE_ANGLE - TOLERANCE || accelAngle > BASE_ANGLE + TOLERANCE) {
    Serial.print("ANGLE TO ADJUST : ");
    Serial.println(adjust(accelAngle));
  }
  servoWrite(adjust(accelAngle), refreshRate);
}

// Servo Control Function -
// Sends signal to Servo: Makes use of <Servo.h> Library, sends a signal to Servo to change its angle.
// Input variables for Requested Angle (int A) and Delay between change (int D)
// Outputs current angle to Serial Monitor
//============================

void servoWrite(int A, int D) {
  servoMain.write(A);        // Rotate Servo to angle A
  //serialOut(servoMain.read());   // Print Servo angle to Serial Monitor
  delay(D);                   // Wait for D milliseconds
}


//============================


//====================== SECONDARY FUNCTIONS =============================\\


// Servo Diagnostic Function -
// Checks the Servo for mechanical failure: uses servoWrite function to rotate Servo Head then pauses.
// Variable D used for delay between angle changes in milliseconds
// Function can also be used to assess maximum servo realignment speed by lowering variable D

void servoDiag() {

  // ! Variable
  int D = 250;          // Delay between change (milliseconds)

  Serial.println("==================================================");
  Serial.print("TEST SPEED : ");
  Serial.print(D);
  Serial.println(" milliseconds");

  // Testing Loop
  // Starting value: beginning angle in degrees -   DEFAULT: 0
  // End Value: Final Angle in degrees -            DEFAULT: 180
  // Increment: Angle change amount in degrees -    DEFAULT: 45
  for (int i = 0; i <= 180; i = i + 20) {
    servoWrite(i, D);
  }

  servoWrite(90, 5000);  // Servo to midpoint and long pause

}

// Serial Handler -
// Message Output: Outputs angle to Serial Monitor with formatting
// Input variable of current angle

void serialOut(int angleMeasure) {
  Serial.print("Current Angle:    ");
  Serial.println(angleMeasure);
}


// Adjustment Calculator -
// Solves for distance to the BASE_ANGLE
// Statement checks to see if current angle is outside of specified boundries

int adjust(int input) {
  if (input < BASE_ANGLE ) {
    return (BASE_ANGLE - input);
  }

  else if ( input > BASE_ANGLE) {
    return (BASE_ANGLE - input);
  }

  else {
    Serial.println("Within Boundries");
    return (BASE_ANGLE);
  }
}
