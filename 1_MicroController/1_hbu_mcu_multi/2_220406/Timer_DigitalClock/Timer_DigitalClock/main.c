/*
 * Timer_DigitalClock.c
 *
 * Created: 2022-04-06 오전 11:42:36
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 1. 타이머를 통해서 초를 측정할 수 있다.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum {C0, C1, C2, C3};
	
unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
								0x7C, 0x07, 0x7F, 0x67, 0x77, 0x7C,
								0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};

unsigned char time_s = 0, time_m = 0, timer0Cnt = 0;

void print_FND(unsigned char selCx, unsigned char data);

ISR(TIMER0_OVF_vect);

int main(void)
{
	
	DDRE = 0xFF;
	PORTE = 0x00;
	DDRG = 0x0F;
	PORTG = 0x0F;
	
	TCCR0 = 0x07;
	
	TCNT0 = 0xff - 80;
	
	TIMSK |= 1 << TOIE0;
	TIFR |= 1 << TOV0;
	
	sei();

    while (1) 
    {
		print_FND(C3, time_s % 10);
		_delay_ms(1);
		
		print_FND(C2, time_s / 10);
		_delay_ms(1);
		
		print_FND(C1, time_m % 10);
		_delay_ms(1);
		
		print_FND(C0, time_m / 10);
		_delay_ms(1);
				
    }
	
	return 0;
	
}

ISR(INT0_vect){
	
	cli();
	TCNT0 = 0xff - 80;
	timer0Cnt++;
	
	if(timer0Cnt == 90){
		
		if(time_s >= 59){
			time_m++;
			time_s = 0;
		}
		
	}else{
		time_s++;
		
		if(time_m > 59){
			time_m = 0;
		}
		
		timer0Cnt = 0;
	
	}
	sei();
	
}

void print_FND(unsigned char selCx, unsigned char data){
	
	switch(selCx){
		
		case C3:
			PORTG &= 0xF0;
			PORTG |= 0x07;
			
			break;
		
		case C2:
			PORTG &= 0xF0;
			PORTG |= 0x0B;
		
			break;
		
		case C1:
			PORTG &= 0xF0;
			PORTG |= 0x0D;
		
			break;
		
		case C0:
			PORTG &= 0xF0;
			PORTG |= 0x0E;
			
			break;
			
		default:
			PORTG &= 0xF0;
			PORTG |= 0x0F;
			
			break;
		
	}
	
	if(selCx == C1 && time_s % 2 == 0){
		PORTE = FND_DATA_TBL[data] | 0x80;
	}else{
		PORTE = FND_DATA_TBL[data];
	}
	
}