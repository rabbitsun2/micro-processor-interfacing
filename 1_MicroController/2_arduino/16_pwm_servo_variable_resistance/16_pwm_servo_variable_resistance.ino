#include <Servo.h>

const int SERVO_MOTOR_PIN = 5;
const int POT_PIN = 0;
const int ON = 1;
const int OFF = 0;

int angle = 0;
Servo servo;

void setup() {
  servo.attach(SERVO_MOTOR_PIN);
  
}

void loop() {

  int reading = analogRead(POT_PIN);
  int angle = reading / 6;
  servo.write(angle);
  
}
