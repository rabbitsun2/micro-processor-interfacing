/*
 * 제목: Btn_LED(버튼 LED 실험)
 * 작성: 정도윤(Doyun Jung)
 * 작성일자: 2022-04-08
 * 비고: 
 */
 
const int LED_BLUE = 3;
const int TOGGLE_BTN = 7;


void setup() {
  Serial.begin(9600);
  pinMode(TOGGLE_BTN, INPUT);
  pinMode(LED_BLUE, OUTPUT);  

}

void loop() {

  int readBtnValue = digitalRead(TOGGLE_BTN);
  Serial.println(readBtnValue);

  delay(100);

  if ( readBtnValue == HIGH ){
    digitalWrite(LED_BLUE, HIGH);
  }
  else{
    digitalWrite(LED_BLUE, LOW);
  }
  
}
