#include <Servo.h>

Servo servoControl;

//Variables
int const potPin = A0; // Potentiometer Control
int potVal; // Potentiometer Value
int angle; // Set angle of Motor

void setup() {
  servoControl.attach(9); // Attaching Servo to pin 9 on Shield
  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(potPin);
  Serial.print("Potentiometer Value: ");
  Serial.print(potVal);

  angle = map(potVal, 0, 1023, 0, 179); // Mapping Potentiometer Value to angle value (1-180);
  Serial.print(", angle: ");
  Serial.print(angle);

  angle = map(potVal , 0, 1023, 0, 179);
  servoControl.write(angle);
  delay(15); // allows time for servo to move to new position

}
