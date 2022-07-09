#include <Servo.h>

const int SERVO_MOTOR_PIN = 5;
const int ON = 1;
const int OFF = 0;

int angle = 0;
Servo servo;

void setup() {
  servo.attach(SERVO_MOTOR_PIN);
  
}

void loop() {

  /*
  for(angle = 0; angle < 180; angle++){
    servo.write(angle);
    delay(15);
  }

  for(angle = 180; angle > 0; angle--){
    servo.write(angle);
    delay(15);
  }

  */
  servo.write(0);
  delay(2000);
  servo.write(180);
  delay(2000);
  
}
