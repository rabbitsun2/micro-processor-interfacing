/* 
 *  프로젝트명: LCD 16x2, yl-38 Sensor(토양 센서) 
 *  작성: 정도윤(Doyun Jung)
 *  작성일자: 2022-04-08
 *  비고:
 *  
 */


#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <String.h>

const int A0_Pin = 0;
const int LED_BLUE = 13;
const int LED_YELLOW = 12;
const int LED_RED = 11;

const int LED_BLUE_2 = 3;

const int TOGGLE_BTN = 7;


int change = 1;
int sensorVal = 0;

// 0x3F I2C 주소를 가지고 있는 16x2 LCD객체를 생성
LiquidCrystal_I2C lcd(0x27, 16, 2);   // 0x27 -> 주소 스캐너로 탐색하여 지정할 것

String yl_sensor();   // 토양 센서
void blinker();     // 신호등
void lcd_print(String header, String body);

void setup() {
  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(LED_BLUE_2, OUTPUT);
  
  pinMode(TOGGLE_BTN, INPUT);

}

void loop() { 
  int readBtnValue = digitalRead(TOGGLE_BTN);

  sensorVal = analogRead(A0_Pin);
  delay(1000);

  // 센서
  String result = yl_sensor();

  // LCD 출력
  String body = "  Doyun Jung!! ";
  lcd_print(result, body);

  // 신호등
  blinker();

  // 버튼 입력 상태 출력
  if ( readBtnValue == HIGH ){
    digitalWrite(LED_BLUE_2, HIGH);
  }
  else{
    digitalWrite(LED_BLUE_2, LOW);
  }
  
  // 1초간 대기합니다.
  delay(1000);
  // LCD의 모든 내용을 삭제합니다.
  lcd.clear();

}

String yl_sensor(){

  String result = "";
  
  if ( sensorVal <= 450 ){
    result = "  Very Wet!";
  }
  else if ( sensorVal > 500 && sensorVal <= 1000 ){
    result = "  It's Ok!";    
  }
  else if ( sensorVal > 1000 ){
    result = "  Very Dry!";
  }
  
  return result;
  
}

void lcd_print(String header, String body){

    lcd.setCursor(0,0);
    lcd.print(header);
    lcd.setCursor(0,1);
    lcd.print(body);
  
}

void blinker(){

  if ( change == 1 ){
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);  

    change = 2;
    
  }
  else if ( change == 2 ){
    digitalWrite(LED_BLUE, LOW);    
    digitalWrite(LED_YELLOW, HIGH); 
    digitalWrite(LED_RED, LOW);   

    change = 3;
    
  }
  else if ( change == 3 ){
    digitalWrite(LED_BLUE, LOW);   
    digitalWrite(LED_YELLOW, LOW); 
    digitalWrite(LED_RED, HIGH);   

    change = 1;
    
  }
  
}
