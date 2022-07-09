/********************************************************************

 ���ϸ� : TextLCD.c
 
 �� �� : 
    "Hello! MCU World !!" ���ڿ��� TextLCD�� ����Ѵ�.

 ��Ʈ���� :
  ��ƮC�� PC0~PC7������ TextLCD�� D0~D7���� �����Ѵ�.
  ��ƮG�� PG0~3�� TextLCD�� RS,RW,E ������ �����Ѵ�.

�ҽ� ���� :
 1) TextLCD�� ����ϱ� ���� ��� ����.
 2) TextLCD�� �ʱ�ȭ�ϴ� �Լ�. 
 3) ���� Ŀ����ġ�� �������� �̵��Ѵ�.
    ù���� �Ű������� ���� �ǹ��ϰ�, �ι��� �Ű������� �����ǹ��Ѵ�.
 4) �ѱ��ھ� ����ϴ� �Լ�.
 5) ���ڿ����� ���ϴ� ���̸�ŭ ����ϴ� �Լ�.
  
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
