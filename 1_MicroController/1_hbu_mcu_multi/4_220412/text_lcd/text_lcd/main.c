/********************************************************************

 파일명 : TextLCD.c
 
 동 작 : 
    "Hello! MCU World !!" 문자열을 TextLCD에 출력한다.

 포트연결 :
  포트C의 PC0~PC7까지는 TextLCD의 D0~D7까지 연결한다.
  포트G의 PG0~3는 TextLCD의 RS,RW,E 순으로 연결한다.

소스 설명 :
 1) TextLCD를 사용하기 위한 헤더 선언.
 2) TextLCD를 초기화하는 함수. 
 3) 현재 커서위치를 왼쪽위로 이동한다.
    첫번쨰 매개변수는 행을 의미하고, 두번쨰 매개변수는 열을의미한다.
 4) 한글자씩 출력하는 함수.
 5) 문자열에서 원하는 길이만큼 출력하는 함수.
  
********************************************************************/

// 1)
#include <avr/io.h>
#include "lcd.h"

int main(){

	// 2)
	lcdInit(); 
 
	// 3)
	lcdGotoXY(0,0);
 
	// 4)
	lcdDataWrite('H');
	lcdDataWrite('e');
	lcdDataWrite('l');
	lcdDataWrite('l');
	lcdDataWrite('o');

	lcdGotoXY(3,1);
 
	// 5)
	lcdPrintData("MCU World !!",12);

	return 0;
	
}
