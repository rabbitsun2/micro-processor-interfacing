/**************************************************************************
 
 파일명 : EXT_SRAM.c
 
 동 작 : 
 터미널 창에서 입력하는 문자열을 외부 SRAM 에 저장한 다음
 TextLCD로 읽어오면서 출력한다.
 
 포트연결
  1) 
  PORTD 0~7핀을 TEXT LCD모듈의 D0~D7 핀에 연결하고
   PORTB 0~2핀을 TEXT LCD모듈의 RS,RW,E핀에 연결한다.
   PB0 -> RS
   PB1 -> RW
   PB2 -> E
 
  2) 
  PORTA 0~7 은 MEMORY모듈의 S_AD0~7으로,
   PORTC 0~7 은 MEMORY모듈의 S_A8~15에 연결한다. 
 
   PA0~7 -> AD0~7 
   PC0~7 -> A0~7 

  3)
  PORTG 0~2를 MEMORY모듈의 S_WR,S_RD,S_ALE 에 연결한다. 
   PG0 -> S_WR
   PG1 -> S_RD
   PG2 -> S_ALE 
  
  4)
    UART모듈의 RX 에는 PE0를 TX에는 PE1를 연결한다.

 소스설명
 1) 외부 메모리 sRAM 의 상위 어드레스로 1바이트의 데이타를 읽고 쓰는 정의 함수
 2) 외부 메모리를 인터페이스 하기 위한 레지스터 설정.
 3) UART0 통신 설정
 4) TextLCDS 초기화
 5) Tab키를 누르거나 입력받은 바이트수가 32가 될떄까지 받은 데이타를 
    SRAM에 저장시킨다.
 6) 받은 데이타수에 따른 TextLCD에 출력할 칸 및 라인수 결정 한후,
    TextLCD에 한글자씩 출력한다.

 참조사항 :
  만약 하이퍼터미널 에서 엔터키를 눌러도 프로그램이 동작하시 않을경우
  하이퍼터미널의 파일 -> 속성 의 설정탭으로 이동후, ASCII 설정을 누른다음.
  ASCII 보내기에서 줄끝에 LF를 붙여 보냄을 테크한후 처음부터 다시 실행해본다.
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
  						"\n\r TextLCD에 출력할 데이타를 입력하세요\n\r"
						" (종료 : Enter키, 32바이트 이내)\n\r" 
						"**************************************\n\r >> ";

	// 2)
	MCUCR |= 0x80; // 외부 메모리 enable
	XMCRA |= 0x40; // lower sector = 0x1100 - 0xffff ,Upper sector = 0x8000 - 0xffff
	XMCRB = 0x00; 
 
	// 3)
	DDRE = 0xfe; // Rx(입력 0), Tx(출력, 1)

	UCSR0A = 0x00;
	UCSR0B = 0x18; // Rx, Tx enable
	UCSR0C = 0x06; // 비동기 방식, No Parity bit, 1 Stop bit
 
	UBRR0H = 0x00;
	UBRR0L = 0x03; //7.3728 MHz -> 115200 bps

	// 4)
	lcdInit(); //TextLCD 초기화 
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
	for(j = 0; j < line1 ; j++){ // 읽어들인 문자열 출력 

		lcdDataWrite(read_XRAM(0x0100+j)); 
		_delay_ms(10); 

	}

	lcdGotoXY(0,1);

	for(j = 0; j < line2; j++){ // 읽어들인 문자열 출력 

		lcdDataWrite(read_XRAM(0x0100+j+line1)); 
		_delay_ms(10); 

	}
 
 
	return 0;

}


