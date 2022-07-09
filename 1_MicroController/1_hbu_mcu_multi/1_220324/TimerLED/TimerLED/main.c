/*
 * TimerLED.c
 *
 * Created: 2022-03-24 12:48:50
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 		1. Hanback Microprocessor Kit (Atmega128)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0;

/*
	SIGNAL(SIG_OVERFLOW0);
	SIGNAL 폐기됨. / ISR로 대체됨.
	SIG_OVERFLOW0 폐기됨. / TIMER0_OVF_vect로 대체됨.
	SIG_OVERFLOW1 폐기됨. / TIMER1_OVF_vect로 대체됨.
*/

ISR(TIMER0_OVF_vect);

int main(void)
{
	DDRE = 0xFF;
	TCCR0 = 0x07;
	
	TCNT0 = 0xff - 72;	// (1 / 7.3728Mhz / 1024 prescalar))* 72 => 0.01s를 얻기 위한 카운트 값
	
	TIMSK |= 1 << TOIE0;	// 오버플로우 인터럽트 허용
	TIFR |= 1 << TOV0;
	
	sei();		// 전역 인터럽트 허용
    /* Replace with your application code */
    while (1) 
    {	
		PORTE = LED_Data;
	}
	
	return 0;
}

ISR(TIMER0_OVF_vect){
	
	cli();		// 인터럽트 클리어(인터럽트 금지)
	TCNT0 = 0xff - 72;
	timer0Cnt++;
	
	if(timer0Cnt == 100){	// 0.01s * 100 = 1s    1초를 얻기 위한 카운트 함수
		LED_Data++;
		timer0Cnt = 0;
	}
	
	sei();		// 인터럽트 허용
	
}
