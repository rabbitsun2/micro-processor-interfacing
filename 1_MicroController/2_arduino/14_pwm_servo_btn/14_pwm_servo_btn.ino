#include <Servo.h>

const int SERVO_PIN = 5;
const int SW_PIN = 7;

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(SERVO_PIN);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {

  if(digitalRead(SW_PIN) == HIGH){
    myservo.write(180);
  }else{
    myservo.write(90);
  }
  
}
