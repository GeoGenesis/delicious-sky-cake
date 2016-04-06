
/*
   Code written by GEORGE GOODSELL
   Student ID: 120015759
   City University, 2016
   THESIS WORK

   References: 
   http://urrg.eng.usm.my/index.php/en/news-and-articles/20-articles/229-pitch-and-roll-angle-measurement-using-accelerometer-adxl-345-and-arduino
   
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

double roll; // Degree measure of angle
double pitch;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// REGISTER REFERENCE
// 0x53 - START TRANSMISSION: ADDRESS OF ACCELEROMETER
// 0x31 - DATA_FORMAT REGISTER
// 0x01 - +/- 4G RANGE SET
// 0x2D - POWER_CTL REGISTER
// 0x08 - ADXL MEASUREMENT MODE

void setup() {
  
 Serial.begin(9600);
 
}

void loop() {
  getAcceleration(false);

}

void accelSetup() {
  
//  displaySetRange(ADXL345_RANGE_16_G);
//  displaySetRange(ADXL345_RANGE_8_G);
//  displaySetRange(ADXL345_RANGE_4_G);
  
// Serial Monitor Output
  accel.setRange(ADXL345_RANGE_2_G); // Set accelerometer sensitivity
  displaySensorDetails(); // Output Sensor Details to Serial Monitor
  displayDataRate(); // Output Data Rate to Serial Monitor
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
  
    roll = (atan2(-y, z)*180)/M_PI;
    pitch = (atan2(x, sqrt(y*y + z*z))*180.0)/M_PI;

    Serial.print("roll: ");
    Serial.print(roll);
    Serial.println(" degrees");
    
    Serial.print("pitch: ");
    Serial.println(pitch);
    Serial.println(" degrees");
}

