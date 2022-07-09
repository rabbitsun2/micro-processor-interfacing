/*
 * Timer_Led.c
 *
 * Created: 2022-04-06 오전 11:35:13
 * Author : 정도윤(Doyun Jung)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0;

ISR(TIMER0_OVF_vect);

int main(void)
{
    DDRE = 0xFF;
	TCCR0 = 0x07;
	
	TCNT0 = 0xff -72;
	
	TIMSK |= 1 << TOIE0;	
	TIFR |= 1 << TOV0;
	
	sei();
	
    while (1) 
    {
		PORTE = LED_Data;
    }
	
	return 0;
	
}

ISR(TIMER0_OVF_vect){
	
	cli();
	TCNT0 = 0xff - 72;
	
	timer0Cnt++;
	
	if(timer0Cnt == 100){
		// 0.01s * 100 = 1s  1초를 얻기 위한 카운트 횟수
		LED_Data++;
		timer0Cnt = 0;
	}
	
	sei();
	
}