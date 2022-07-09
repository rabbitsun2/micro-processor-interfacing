/**************************************************************************
 
 ���ϸ� : EXT_SRAM.c
 
 �� �� : 
 �͹̳� â���� �Է��ϴ� ���ڿ��� �ܺ� SRAM �� ������ ����
 TextLCD�� �о���鼭 ����Ѵ�.
 
 ��Ʈ����
  1) 
  PORTD 0~7���� TEXT LCD����� D0~D7 �ɿ� �����ϰ�
   PORTB 0~2���� TEXT LCD����� RS,RW,E�ɿ� �����Ѵ�.
   PB0 -> RS
   PB1 -> RW
   PB2 -> E
 
  2) 
  PORTA 0~7 �� MEMORY����� S_AD0~7����,
   PORTC 0~7 �� MEMORY����� S_A8~15�� �����Ѵ�. 
 
   PA0~7 -> AD0~7 
   PC0~7 -> A0~7 

  3)
  PORTG 0~2�� MEMORY����� S_WR,S_RD,S_ALE �� �����Ѵ�. 
   PG0 -> S_WR
   PG1 -> S_RD
   PG2 -> S_ALE 
  
  4)
    UART����� RX ���� PE0�� TX���� PE1�� �����Ѵ�.

 �ҽ�����
 1) �ܺ� �޸� sRAM �� ���� ��巹���� 1����Ʈ�� ����Ÿ�� �а� ���� ���� �Լ�
 2) �ܺ� �޸𸮸� �������̽� �ϱ� ���� �������� ����.
 3) UART0 ��� ����
 4) TextLCDS �ʱ�ȭ
 5) TabŰ�� �����ų� �Է¹��� ����Ʈ���� 32�� �ɋ����� ���� ����Ÿ�� 
    SRAM�� �����Ų��.
 6) ���� ����Ÿ���� ���� TextLCD�� ����� ĭ �� ���μ� ���� ����,
    TextLCD�� �ѱ��ھ� ����Ѵ�.

 �������� :
  ���� �������͹̳� ���� ����Ű�� ������ ���α׷��� �����Ͻ� �������
  �������͹̳��� ���� -> �Ӽ� �� ���������� �̵���, ASCII ������ ��������.
  ASCII �����⿡�� �ٳ��� LF�� �ٿ� ������ ��ũ���� ó������ �ٽ� �����غ���.
***************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

// 1)
#define read_XRAM(address) (*(volatile unsigned char *)(0x1100+address))
#define write_XRAM(address,value) ((*(volatile unsigned char *)(0x1100+address))=value)

void putch(unsigned char data){

	while((UCSR0A & 0x20) == 0); 
	UDR0 = data;
	UCSR0A |= 0x20;
}


unsigned char getch(){
	
	unsigned char data;

	while((UCSR0A & 0x80)==0);

	data=UDR0;

	UCSR0A |= 0x80;
	return data;

}

unsigned char msg_Buf[32]={0};

int main(){

	unsigned char i=0,j=0;
	unsigned char line1,line2;
	unsigned char Tmp=0; 
	unsigned char text[]="\n\r**************************************"
 						"\n\r EXT-SRAM TEST Program ! "
  						"\n\r TextLCD�� ����� ����Ÿ�� �Է��ϼ���\n\r"
						" (���� : EnterŰ, 32����Ʈ �̳�)\n\r" 
						"**************************************\n\r >> ";

	// 2)
	MCUCR |= 0x80; // �ܺ� �޸� enable
	XMCRA |= 0x40; // lower sector = 0x1100 - 0xffff ,Upper sector = 0x8000 - 0xffff
	XMCRB = 0x00; 
 
	// 3)
	DDRE = 0xfe; // Rx(�Է� 0), Tx(���, 1)

	UCSR0A = 0x00;
	UCSR0B = 0x18; // Rx, Tx enable
	UCSR0C = 0x06; // �񵿱� ���, No Parity bit, 1 Stop bit
 
	UBRR0H = 0x00;
	UBRR0L = 0x03; //7.3728 MHz -> 115200 bps

	// 4)
	lcdInit(); //TextLCD �ʱ�ȭ 
	ms_delay(100);	
	UDR0 = 0;

	// 5)
	while(text[j]!='\0')
		putch(text[j++]);
	
	while(1){
 
		Tmp = getch();
		putch(Tmp);
	  
		if((Tmp == '\r') || i > 32) {
			break;
		}
 
		write_XRAM(0x0100+i,Tmp); 
		_delay_ms(10); 
		
		i++;

	}
 
	// 6)
	if(i<=16){
		line1 = i;
		line2 =0;
	}
	else{
		line1 = i - (i-16);
		line2 = i-16-1;
	}


	_delay_ms(100);
 
	// 7)
	for(j = 0; j < line1 ; j++){ // �о���� ���ڿ� ��� 

		lcdDataWrite(read_XRAM(0x0100+j)); 
		_delay_ms(10); 

	}

	lcdGotoXY(0,1);

	for(j = 0; j < line2; j++){ // �о���� ���ڿ� ��� 

		lcdDataWrite(read_XRAM(0x0100+j+line1)); 
		_delay_ms(10); 

	}
 
 
	return 0;

}


