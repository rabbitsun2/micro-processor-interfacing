/*
 *    작품명: Pitches
 *    작성일자: 2022-04-26
 *    작성자: 정도윤(Doyun Jung)
 *    비고:
 */

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#include "pitches.h"

const int BTN_1_PIN = 2;
const int SENSOR_DHT_PIN = A0;
const int speakerpin = 8;

// 음계 데이터
int melody[] = {NOTE_G7, NOTE_G7, NOTE_A7, NOTE_A7, NOTE_G7,
            NOTE_G7, NOTE_E7, NOTE_G7, NOTE_G7, NOTE_E7,
            NOTE_E7, NOTE_D7, NOTE_G7, NOTE_G7, NOTE_A7,
            NOTE_A7, NOTE_G7, NOTE_G7, NOTE_E7, NOTE_G7,
            NOTE_E7, NOTE_D7, NOTE_E7, NOTE_C7};

// 음의 길이, 4:4분음표, 2:2분음표
int noteDurations[] = {4,4,4,4,4,4,2,4,4,4,4,1,4,4,4,4,4,4,2,4,4,4,4,1};

void play();

void setup() {

  Serial.begin(115200);
  pinMode(BTN_1_PIN, INPUT);
  
}

void loop() {

  int btn = digitalRead(BTN_1_PIN);
  DHT.read(SENSOR_DHT_PIN);
  
  Serial.print(digitalRead(BTN_1_PIN));  
  Serial.print("/");
  Serial.print("온도:");
  Serial.print(DHT.temperature);
  Serial.print("습도:");
  Serial.print(DHT.humidity);

  Serial.println();

  // 버튼을 눌렀을 때
  if ( btn == 1 ){
    play();
  }

  // 25도 이상일 때
  if ( (int) DHT.temperature > 27 ){
    play();
  }
  
  delay(1000);
}


void play(){

  for (int thisNote = 0; thisNote < 24; thisNote++){
    int noteDuration = 1000 / noteDurations[thisNote];

    tone(speakerpin, melody[thisNote], noteDuration );

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(speakerpin);
    
  }
  
}
