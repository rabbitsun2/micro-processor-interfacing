/*
 * 제목: Btn_LED(버튼 LED 실험)
 * 작성: 정도윤(Doyun Jung)
 * 작성일자: 2022-04-08
 * 비고: 
 */
 
const int LED_BLUE = 3;
const int TOGGLE_BTN = 7;

const int PULL_UP = 1;
const int PULL_DOWN = 0;

const int END_CNT = 5;

int readBtnValue = 0;
int toggle = 0;


void setup() {
  
  Serial.begin(9600);
  pinMode(TOGGLE_BTN, INPUT);
  pinMode(LED_BLUE, OUTPUT);  

}

void loop() {

  readBtnValue = digitalRead(TOGGLE_BTN);
  Serial.println(readBtnValue);
  
  if ( readBtnValue == PULL_UP ){
    toggle = 1;
  }
  else if ( readBtnValue == PULL_DOWN ){
    toggle = 0;
  }

  if ( toggle == 1 ) {
    digitalWrite(LED_BLUE, HIGH);
  }
  else {
    digitalWrite(LED_BLUE, LOW);
  }

  while(digitalRead(TOGGLE_BTN));

  // 락 기능
  delay(100);
  
}
