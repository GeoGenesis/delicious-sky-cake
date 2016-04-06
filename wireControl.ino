
void wireSetup() {
  
  Wire.beginTransmission(0x53);   // Begin transmission at this register
  Wire.write(0x31);               // Set Data Format
  Wire.write(0x01);               // Set accelerometer tolerance
  Wire.endTransmission();         // End transmission

  Wire.beginTransmission(0x53);   // Begin transmission
  Wire.write(0x2D);               // Power Control
  Wire.write(0x08);               // Put Accelerometer into Measurement Mode
  Wire.endTransmission();         // End Transmission
  
}

void wireLoop(){
  byte _buffer[6];
  int i = 0;
  float alpha = 0.5;

  Wire.beginTransmission(0x53);
  Wire.write(0x32);
  Wire.endTransmission();
  Wire.beginTransmission(0x53);
  Wire.requestFrom(0x53, 6);
  while(Wire.available()) {
  _buffer[i] = Wire.read();
    i++;}
Wire.endTransmission();

float x = (((int)_buffer[1]) << 8) | _buffer[0];
float y = (((int)_buffer[3]) << 8) | _buffer[2];
float z = (((int)_buffer[5]) << 8) | _buffer[4];

x *= 0.0078;
y *= 0.0078;
z *= 0.0078;

roll = (atan2(-y, z)*180)/M_PI;
pitch = (atan2(x, sqrt(y*y + z*z))*180.0)/M_PI;

Serial.print("roll: ");
Serial.println(roll);

Serial.print("pitch: ");
Serial.println(pitch);

delay(100);
}

