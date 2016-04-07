/*
   Code written by GEORGE GOODSELL
   Student ID: 120015759
   City University, 2016
   THESIS WORK
*/

/* MATERIAL REFERENCES: 
   =====================================================
   http://urrg.eng.usm.my/index.php/en/news-and-articles/20-articles/229-pitch-and-roll-angle-measurement-using-accelerometer-adxl-345-and-arduino
   http://www.st.com/web/en/resource/technical/document/application_note/CD00268887.pdf
   http://www.hobbytronics.co.uk/accelerometer-info

     
   REGISTER REFERENCES:
   =====================================================
   0x53 - START TRANSMISSION: ADDRESS OF ACCELEROMETER
   0x31 - DATA_FORMAT REGISTER
   0x01 - +/- 4G RANGE SET
   0x2D - POWER_CTL REGISTER
   0x08 - ADXL MEASUREMENT MODE

   EQUATION REFERENCE:
   =====================================================
   Three-axis Tilt Angle Equations:
    
   Roll angle = arctan( -(G_x)/(G_z) )
   Pitch angle = arctan G_y / ( sqrt(( G_x^2 ) + (G_z^2) ) )
   
*/

#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Servo servoMain; // Servo Define

int SERIAL_REFRESH_RATE = 9600; // Setting for Serial Port Data Rate
int SERVO_PIN = 10; // Servo-connected Pin

// Update Speed - How quickly the angle is adjusted (refresh rate) in Milliseconds
// DEFAULT: 100
int SYSTEM_REFRESH_RATE = 100;

// Set angle - system will work to adjust itself to this angle
// DEFAULT: 0
int BASE_ANGLE = 0;

// Degrees of Tolerance - how many degrees rig can be rotated before activating system
// DEFAULT: 5
int TOLERANCE = 5;

// Angle Measurements - values of system tilt
double roll; // Degree measure of angle
double pitch;

// ACCELEROMETER OBJECT: UNIQUE IDENTIFIER 120015759
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(120015759);

//==================== SETUP + LOOP FUNCTIONS =========================\\

void setup()
{
  // Attach Servo and Accelerometer to board
  accel.begin();
  servoMain.attach(SERVO_PIN); // Servo attached on digital pin 10
  
  Serial.begin(SERIAL_REFRESH_RATE); // Starts Serial Monitor

    // Check to see that Accelerometer is functional
  if(!accel.begin())
  {
    /* Freezes Serial Prompt if accelerometer doesn't initialize */
    Serial.println("ADXL345 not detected - check wiring.");
    while(1);
  }

  // Set Accelerometer Sensitivity
  accel.setRange(ADXL345_RANGE_4_G); // Set accelerometer sensitivity (+/- 2G, 4G, 8G, 16G) - DEFAULT: 2G
  
}

void loop()
{
//  sensors_event_t event;
//  accel.getEvent(&event);
//  double roll = calculateRoll(event.acceleration.y, event.acceleration.z);
//  double adjusted = map(roll, -90, 90, 0, 180);
//  
//  servoWrite(adjusted, SYSTEM_REFRESH_RATE);

  one2one();
}

//====================== PRIMARY FUNCTIONS =============================\\

void one2one(){
//============================
// Accelerometer-to-Servo communication Function -
// Sends signal to Servo based on current angle of Accelerometer, maps angle to Servo Range
// Input variables for Requested Angle (int A) and Delay between change (int D)
// Outputs current angle to Serial Monitor
//============================

  sensors_event_t event;
  accel.getEvent(&event);

  double roll = calculateRoll(event.acceleration.y, event.acceleration.z);
  double adjusted = map(roll, -90, 90, 0, 180);
  
  servoWrite(adjusted, SYSTEM_REFRESH_RATE);
}

void correct() {
  //============================
  // Correction Function -
  // Uses the adjust function to solve for correction angle, sends signal to Servo to fix.
  // Input is the angle from the Accelerometer
  //============================

    // Create events for accelerometer data
    sensors_event_t event;
    accel.getEvent(&event);

    double accelAngle = calculateRoll(event.acceleration.y, event.acceleration.z);

  // Check to see if value needs to be adjusted (outside of accepted boundries)
    if (accelAngle < (BASE_ANGLE - TOLERANCE) || accelAngle > (BASE_ANGLE + TOLERANCE)) {

    Serial.print("OFFSET ANGLE : ");
    servoWrite(adjust(accelAngle), SYSTEM_REFRESH_RATE);
    
    Serial.println(adjust(accelAngle));
  }
  else{
    delay(50);
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

  servoMain.write(A);            // Rotate Servo to angle A
  serialOut(servoMain.read());   // Print Servo angle to Serial Monitor
  delay(D);                      // Wait for D milliseconds
}


//====================== SECONDARY FUNCTIONS =============================\\


double calculateRoll(double y, double z) {
  roll = (atan2(-y, z)*180)/M_PI;
  delay(SYSTEM_REFRESH_RATE);
  return roll;
}

double calculatePitch(double x, double y, double z) {
  pitch = (atan2(x, sqrt(y*y + z*z))*180.0)/M_PI;
  return pitch;
}


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
