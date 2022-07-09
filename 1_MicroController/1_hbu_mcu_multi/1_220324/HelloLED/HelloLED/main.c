/*
 * HelloLED.c
 *
 * Created: 2022-03-23 14:40:35
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 		1. Hanback Microprocessor Kit (Atmega128)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//unsigned char cnt = 0;
int main(){
	
	char i;
	unsigned char LED_Data = 0x00;
	
	DDRE = 0xFF;
	
	while(1){
		
		PORTE = LED_Data;	// 2吏꾩닔 �삎�떇�쑝濡� �젏�벑
		// PORTE = 1;
		// PORTE = 2;
		// PORTE = 3;
		LED_Data++;
		
		for(i = 0; i < 100; i++){
			_delay_ms(10);
		}
		
	}

	return 0;

}
