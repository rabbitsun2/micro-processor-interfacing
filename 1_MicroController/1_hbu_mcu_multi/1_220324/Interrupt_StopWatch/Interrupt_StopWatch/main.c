/*
 * Interrupt_StopWatch.c
 *
 * Created: 2022-03-23 15:51:02
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 		1. Hanback Microprocessor Kit (Atmega128)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int cnt_zero,cnt_one;

unsigned char time_10ms = 0, time_100ms = 0, time_1s = 0, time_10s = 0;
char Time_STOP = 0;

/* SIGNAL, SIG_INTERRUPT0, SIG_INTERRUPT1 폐기됨.
	SIGNAL 대체 = ISR
	SIG_INTERRUPT0 대체 = INT0_vect
	SIG_INTERRUPT1 대체 = INT1_vect
*/

//SIGNAL(SIG_INTERRUPT0);
//SIGNAL(SIG_INTERRUPT1);

ISR(INT0_vect);
ISR(INT1_vect);

int main(void)
{
	
	unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
									0x6D, 0x7C, 0x07, 0x7F, 0x67,
									0x77, 0x7C, 0x39, 0x5E, 0x79,
									0x08, 0x80};
									
	DDRD = 0xFC;
	
	DDRG = 0x0F;
	DDRE = 0xFF;
	
	EICRA = 0x0F;
	EICRB = 0x00;
	EIMSK = 0x03;
	
	EIFR = 0x03;
	
	sei();
	
    while (1) 
    {
		PORTG = 0x07;
		PORTE = FND_DATA_TBL[time_100ms];
		
		_delay_ms(100);
		PORTG = 0x0B;
		
		PORTG = 0x0D;
		PORTE = FND_DATA_TBL[time_1s];
		_delay_ms(1000);
		
		PORTG = 0x0E;
		PORTE = FND_DATA_TBL[time_10s];
		_delay_ms(1000);
		
		if(Time_STOP == 1)
			continue;
			
		time_10ms++;
		if(time_10ms == 10){
			time_10ms = 0;
			time_100ms++;
		}
		
		if(time_100ms == 10){
			time_100ms = 0;
			time_1s++;
		}
		
		if(time_1s == 10){
			time_1s = 0;
			time_10s++;
		}
		
		if(time_10s == 10){
			time_10s = 0;
			
		}
		
    }
	
	return 0;
}



ISR(INT0_vect){
	
	cli();		// 인터럽트 금지
	if(Time_STOP == 0){
		Time_STOP = 1;
	}
	else{
		Time_STOP = 0;
	}
	sei();		// 전역 인터럽트 허용
}

ISR(INT1_vect){
	
	cli();		// 인터럽트 금지
	
	time_10ms = 0;
	time_100ms = 0;
	time_1s = 0;
	time_10s = 0;
	
	sei();		// 전역 인터럽트 허용
	
}

/* 폐기됨.

SIGNAL(SIG_INTERRUPT0){
	
	cli();
	if(Time_STOP == 0){
		Time_STOP = 1;
	}
	else{
		Time_STOP = 0;
	}
	sei();
}

SIGNAL(SIG_INTERRUPT1){
	
	cli();
	time_10ms = 0;
	time_100ms = 0;
	time_1s = 0;
	time_10s = 0;
	sei();
	
}

*/
