#include <Servo.h>

const int SERVO_PIN = 5;
const int SW_PIN = 7;

Servo myservo;

int cnt = 0;

void setup() {

  Serial.begin(115200);
  myservo.attach(SERVO_PIN);
  pinMode(SW_PIN, INPUT);
  
}

void loop() {

  // 버튼 눌렀을 때
  if(digitalRead(SW_PIN) == HIGH){
    cnt++;
  }

  Serial.print(digitalRead(SW_PIN));
  Serial.print("/");
  Serial.println(cnt);

  if ( cnt == 1 ){
    myservo.write(0);
    delay(500);
    myservo.write(180);
    delay(500);
  }
  else if ( cnt == 2 ){
    cnt = 0;
  }

  delay(100); 
  
}
