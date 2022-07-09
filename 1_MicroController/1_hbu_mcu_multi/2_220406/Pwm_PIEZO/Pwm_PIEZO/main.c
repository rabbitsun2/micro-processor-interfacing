/*
 * Pwm_PIEZO.c
 *
 * Created: 2022-04-06 오후 1:44:19
 * Author : 정도윤
 * Constraint(제약사항):
 * 1. 버튼 불량
 * 2. 케이블 없음
 * Result: 
 * 1. 부저 소리 살짝 들림.
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define FREQ(x) (unsigned int)(7372800 /(2*(x)))

void Change_FREQ(unsigned int freq);
void STOP_FREQ();

void Pop_Button();
unsigned char Push_Button();
unsigned int key2DoReMi(unsigned char key);


int main(void)
{
	unsigned char piano = 0;
	DDRE = 0x08;
	
	TCCR3A |= 0x40;
	TCCR3B |= 0x19;
	
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	STOP_FREQ();
	
	while (1) 
    {
		piano = Push_Button();
		Change_FREQ(key2DoReMi(piano));
		Pop_Button();
		STOP_FREQ();
		
    }
	
	return 0;
	
}


void Change_FREQ(unsigned int freq){
	
	unsigned int x;
	TCCR3A |= 0x40;
	TCCR3B |= 0x19;
	
	do{
		x = TCNT3;
		
	}while(x>= FREQ(freq));
	
	ICR3 = FREQ(freq);
	
}

void STOP_FREQ(){
	
	TCCR3A = 0x00;
	TCCR3B = 0x00;
	TCNT3 = 0;
	ICR3 = FREQ(0);
	PORTE = 0xFF;
	
}

void Pop_Button(){
	while((PIND & 0xFF)!= 0x00);
}

unsigned char Push_Button(){
	
	while((PIND & 0xFF) == 0x00);
	return PIND;
	
}

unsigned int key2DoReMi(unsigned char key){
	
	unsigned int _ret = 0;
	
	switch(key){
		
		case 0x01:
			_ret = 523;
			break;
			
		case 0x02:
			_ret = 587;
			break;
		
		case 0x04:
			_ret = 659;
			break;
			
		case 0x08:
			_ret = 698;
			break;
			
		case 0x10:
			_ret = 783;
			break;
		
		case 0x20:
			_ret = 880;
			break;
			
		case 0x40:
			_ret = 987;
			break;
			
		case 0x80:
			_ret = 1046;
			break;
		
	}
	
	return _ret;
}