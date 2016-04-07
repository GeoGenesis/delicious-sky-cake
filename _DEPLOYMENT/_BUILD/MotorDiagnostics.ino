
/*
   Code written by GEORGE GOODSELL
   Student ID: 120015759
   City University, 2016
   THESIS WORK
*/

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
    
  Serial.println("====== RESET ======");
  servoWrite(90, 5000);  // Servo to midpoint and long pause
  Serial.println("");
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

void speedTest(){
  //============================
  // Servo Max Speed Test -
  // Assesses the Servo's maximum response time between changes
  // Uses customDiag() function to test max speed by decreasing delays between steps (shift states)
  //============================

  //Testing Variables
  int _start = 0; // Starting Angle -  DEFAULT: 0
  int _end = 180; // End Angle -       DEFAULT: 180
  int inc = 45; // Increment angle -   DEFAULT: 45
  
  // Left to Right rotation

  Serial.println("========== Servo Response Time Test ========== ");
  Serial.println("");
  
  // ---- Low respnse time
  Serial.println("1000-500 millisecond Response Time");
  customDiag(_start, _end, inc, 1000); // 1 second step
  customDiag(_start, _end, inc, 750); // .75 seconds step
  customDiag(_start, _end, inc, 500); // .50 seconds step
  
  // ---- Mid response time
  Serial.println("500-200 millisecond Response Time");
  customDiag(_start, _end, inc, 333); // .33 seconds step
  customDiag(_start, _end, inc, 250); // .25 seconds step
  customDiag(_start, _end, inc, 200); // .20 second step

  // ---- Fast response time
  Serial.println("150-75 millisecond Response Time");
  customDiag(_start, _end, inc, 150); // .15 second step
  customDiag(_start, _end, inc, 100); // .1 second step
  customDiag(_start, _end, inc, 75); // .075 second step
  Serial.println("");

  // Right to Left rotation

  // ---- Low respnse time
  Serial.println("1000-500 millisecond Response Time");
  customDiag(_end, _start, inc, 1000); // 1 second step
  customDiag(_end, _start, inc, 750); // .75 seconds step
  customDiag(_end, _start, inc, 500); // .50 seconds step

  Serial.println("500-200 millisecond Response Time");
  // ---- Mid response time
  customDiag(_end, _start, inc, 333); // .33 seconds step
  customDiag(_end, _start, inc, 250); // .25 seconds step
  customDiag(_end, _start, inc, 200); // .20 second step

  // ---- Fast response time
  Serial.println("150-75 millisecond Response Time");
  customDiag(_end, _start, inc, 150); // .15 second step
  customDiag(_end, _start, inc, 100); // .1 second step
  customDiag(_end, _start, inc, 75); // .075 second step

  Serial.println("");
}

void angleTest() {
  //============================
  // Servo Angle Range Test -
  // Assesses the Servo Head's angular reach (in degrees)
  // Uses customDiag() function to test max range of servo
  //============================
  
  int _start = 0; // Starting Angle -  DEFAULT: 0
  int _end = 180; // End Angle -       DEFAULT: 180
  int inc = 45; // Increment angle -   DEFAULT: 10
    
  customDiag(_end, _start, inc, 1000);
}
