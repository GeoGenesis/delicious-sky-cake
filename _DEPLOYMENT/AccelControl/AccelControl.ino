
/*
   Code written by GEORGE GOODSELL
   Student ID: 120015759
   City University, 2016
   THESIS WORK

   MATERIAL REFERENCES: 
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

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

double roll; // Degree measure of angle
double pitch;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(120015759);

void setup() {
  
 accel.begin();
 Serial.begin(9600);

  // Initialize accelerometer
  if(!accel.begin())
  {
    /* Throws a Serial Prompt if accelerometer doesn't initialize */
    Serial.println("ADXL345 not detected - check wiring.");
    while(1);
  }
  
// Serial Monitor Output
  accel.setRange(ADXL345_RANGE_4_G); // Set accelerometer sensitivity (+/- 2G, 4G, 8G, 16G);
  sensorInfo();
  Serial.println("");

}

void loop() {
  getAcceleration(false);

}

void getAcceleration(bool debug){

  sensors_event_t event;
  accel.getEvent(&event);

  if(debug = true){
      Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
      Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
      Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
      delay(500);
      Serial.println("===================================");
  }
  
  calculate(event.acceleration.x,event.acceleration.y,event.acceleration.z);
  
}

void calculate(int x, int y, int z) {

  /* EQUATION REFERENCE
   * =====================================================
   * 
   * Three-axis Tilt Angle Equations:
   * 
   * Roll angle = arctan( -(G_x)/(G_z) )
   * Pitch angle = arctan G_y / ( sqrt(( G_x^2 ) + (G_z^2) ) )
   * 
   */

  roll = (atan2(-y, z)*180)/M_PI;
  pitch = (atan2(x, sqrt(y*y + z*z))*180.0)/M_PI;

  Serial.print("roll: ");
  Serial.print(roll);
  Serial.print(" degrees");
  
  Serial.print("      pitch: ");
  Serial.print(pitch);
  Serial.println(" degrees");
}


