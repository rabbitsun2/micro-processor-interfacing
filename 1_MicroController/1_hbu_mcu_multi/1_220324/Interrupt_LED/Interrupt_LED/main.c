/*
 * Interrupt_LED.c
 *
 * Created: 2022-03-23 15:29:49
 * Author : Doyun Jung(정도윤)
 * Description:
 * 		1. Hanback Microprocessor Kit (Atmega128)
 *                
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char Time_STOP = 0;
ISR(INT0_vect);

/*
	SIGNAL, SIG_INTERRUPT 폐기됨.
	ISR로 대체됨.
 
   ISR(Vector Name){
		// Vector Name: 인터럽트 종류, Interrupt Vector
		// ISR User Code
   }
*/

int main(void)
{

	unsigned char LED_Data = 0x01;
    
	DDRD = 0xFE;
	DDRE = 0xFF;
	EICRA = 0x0F;
	EICRB = 0x00;
	EIMSK = 0x01;
	EIFR = 0x01;
	
	sei();			// 인터럽트 허용(Set Enabled Interrupt) - 전역 인터럽트 허용
	
    while (1) 
    {
		PORTE = LED_Data;
		
		if (Time_STOP == 0 ){
			
			if(LED_Data == 0x80){
				LED_Data = 0x01;
			}else{
				LED_Data <<= 1;
			}
			
		}
		_delay_ms(1000);
		
    }
	
	return 0;
	
}

ISR(INT0_vect){
	
	cli();			// Clear Interrupt - 인터럽트 금지
	if(Time_STOP == 0){
		Time_STOP = 1;
		}else{
		Time_STOP = 0;
	}
	
	sei();
	
}

/* 폐기됨.
SIGNAL(SIG_INTERRUPT0){
	
	cli();
	if(Time_STOP == 0){
		Time_STOP = 1;
	}else{
		Time_STOP = 0;
	}
	
	sei();
}

*/
