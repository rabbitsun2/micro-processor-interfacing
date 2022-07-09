// LCD를 쉽게 제어하기 위한 라이브러리를 추가합니다.
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// 0x3F I2C 주소를 가지고 있는 16x2 LCD객체를 생성합니다.(I2C 주소는 LCD에 맞게 수정해야 합니다.)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() { 

  int value = random(0, 3);
  
  if (value == 0) {
    // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.setCursor(0,0);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print("  Doyun Jung  ");       // 문구를 출력합니다.
  }
  // 랜덤 값이 1이라면 아래의 조건을 실행합니다.
  else if (value == 1) {
    lcd.setCursor(0,1);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print("  Hello World!!  ");     // 문구를 출력합니다.
  }
  // 랜덤 값이 2이라면 아래의 조건을 실행합니다.
  else if (value == 2) {
    // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.setCursor(0,0);
    // 아래의 문장을 출력합니다.
    lcd.print("  Doyun Jung  ");

    lcd.setCursor(0,1);
    lcd.print("  Hello World!!  ");
    
  }
  // 1초간 대기합니다.
  delay(1000);
  // LCD의 모든 내용을 삭제합니다.
  lcd.clear();
}
