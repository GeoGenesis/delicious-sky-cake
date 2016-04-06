/*
   Code written by GEORGE GOODSELL
   Student ID: 120015759
   City University, 2016
   THESIS WORK
*/

#include <Servo.h>

Servo servoMain; // Servo Define

int SERIAL_REFRESH_RATE = 9600; // Setting for Serial Port Data Rate
int SERVO_PIN = 10; // Servo-connected Pin

// Update Speed - How quickly the angle is adjusted (refresh rate) in Milliseconds
// DEFAULT: 1000
int SYSTEM_REFRESH_RATE = 1000;

// Set angle - system will work to adjust itself to this angle
// DEFAULT: 90
int BASE_ANGLE = 90;

// Degrees of Tolerance - how many degrees rig can be rotated before activating system
// DEFAULT: 5
int TOLERANCE = 5;

//==================== SETUP + LOOP FUNCTIONS =========================\\

void setup()
{
  servoMain.attach(SERVO_PIN); // Servo attached on digital pin 10
  Serial.begin(SERIAL_REFRESH_RATE); // Starts Serial Monitor
}

void loop()
{
   
  //  correct(random(0, 180));
  //  delay(3000);
  
}

//====================== PRIMARY FUNCTIONS =============================\\

void correct(int accelAngle) {
  //============================
  // Correction Function -
  // Uses the adjust function to solve for correction angle, sends signal to Servo to fix.
  // Input is the angle from the Accelerometer
  //============================

  // Check to see if value needs to be adjusted (outside of accepted boundries)
  if (accelAngle < BASE_ANGLE - TOLERANCE || accelAngle > BASE_ANGLE + TOLERANCE) {

    //debug(accelAngle);

    Serial.print("OFFSET ANGLE : ");
    servoWrite(adjust(accelAngle), SYSTEM_REFRESH_RATE);
    
    Serial.println(adjust(accelAngle));
  }
  Serial.println("Adjusted.");
  Serial.println("==================================================");
}

void servoWrite(int A){
//============================
// Servo Control Function -
// Sends signal to Servo: Makes use of <Servo.h> Library, sends a signal to Servo to change its angle.
// Input variables for Requested Angle (int A) and Delay between change (int D)
// Outputs current angle to Serial Monitor
//============================

  servoMain.write(A);        // Rotate Servo to angle A
  //serialOut(servoMain.read());   // Print Servo angle to Serial Monitor
}

void servoWrite(int A, int D) {
  //============================
  // Servo Control Function -
  // Sends signal to Servo: Makes use of <Servo.h> Library, sends a signal to Servo to change its angle.
  // Input variables for Requested Angle (int A) and Delay between change (int D)
  // Outputs current angle to Serial Monitor
  //============================

  servoMain.write(A);        // Rotate Servo to angle A
  serialOut(servoMain.read());   // Print Servo angle to Serial Monitor
  delay(D);                   // Wait for D milliseconds
}


//====================== SECONDARY FUNCTIONS =============================\\


void serialOut(int angleMeasure) {
  //============================
  // Serial Handler -
  // Message Output: Outputs angle to Serial Monitor with formatting
  // Input variable of current angle
  //============================

  Serial.print("Current Angle:    ");
  Serial.println(angleMeasure);
}

int adjust(int input) {
  //============================
  // Adjustment Calculator -
  // Solves for distance to the BASE_ANGLE
  // Statement checks to see if current angle is outside of specified boundries
  //============================

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

//====================== DIAGNOSTIC FUNCTIONS ============================\\

void servoDiag() {
  //============================
  // Servo Diagnostic Function -
  // Checks the Servo for mechanical failure: uses servoWrite function to rotate Servo Head then pauses.
  // Variable D used for delay between angle changes in milliseconds
  // Function can also be used to assess maximum servo realignment speed by lowering variable D
  //============================

  // ! Variable
  int D = 250;  // Delay between changes (milliseconds)

  Serial.println("==================================================");
  Serial.print("TEST SPEED : ");
  Serial.print(D);
  Serial.println(" milliseconds / change");

  // Testing Loop
  // Starting value: beginning angle in degrees -   DEFAULT: 0
  // End Value: Final Angle in degrees -            DEFAULT: 180
  // Increment: Angle change amount in degrees -    DEFAULT: 45
  for (int i = 0; i <= 180; i = i + 20) {
    servoWrite(i, D);
  }

  servoWrite(90, 5000);  // Servo to midpoint and long pause
}

void customDiag(int A, int B, int I, int wait) {
  //============================
  // Alternate Servo Diagnostic Function -
  // Checks the Servo for mechanical failure with user-input settings - uses servoWrite function to rotate Servo Head then pauses.
  // Inputs used to control angle range
  // Function can also be used to assess maximum servo realignment speed by lowering variable D
  //============================

  Serial.println("==================================================");
  Serial.print("TEST SPEED : ");
  Serial.print(wait);
  Serial.println(" milliseconds / change");

  // Testing Loop
  // Starting value: beginning angle in degrees -   DEFAULT: 0
  // End Value: Final Angle in degrees -            DEFAULT: 180
  // Increment: Angle change amount in degrees -    DEFAULT: 45

// If Start is smaller than final, change until Start is Final
  if ( A < B ) {
    for (A, B, I; A <= B; A = A + I) {
      servoWrite(A, wait);
    }
  }
  else if (A > B) {
    for (A, B, I; A >= B; A = A - I) {
      servoWrite(A, wait);
    }
  }
    
  Serial.println("RESET");
  servoWrite(90, 5000);  // Servo to midpoint and long pause
}

void debug(double accelAngle) {
  //============================
  // Debugging tool -
  // Print the Accelerometer Angle and Current Servo Angle to the Serial Monitor.
  // Input is the angle from the Accelerometer
  //============================
  Serial.print("ACCELEROMETER ANGLE: ");
  Serial.println(accelAngle);
  Serial.print("SERVO ANGLE: ");
  Serial.println(servoMain.read());

}

