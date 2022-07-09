/*
 * Interrupt_StopWatch.c
 *
 * Created: 2022-04-06 오전 10:50:00
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 1. 버튼을 누르면, 숫자가 정지된다.
 * 2. 버튼을 누르면, 숫자가 계속된다.
 */ 

//#define F_CPU 1600000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char time_10ms = 0;
unsigned char time_100ms = 0;
unsigned char time_1s = 0;
unsigned char time_10s = 0;

char Time_Stop = 0;

ISR(INT0_vect);
ISR(INT1_vect);


int main(void)
{
	unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 
									0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E,
									0x79, 0x71, 0x08, 0x80};
	
	DDRD = 0xFC;		/* 포트 D의 0, 1번째 레지스터를 사용하여 입력
						  (0xFC는 2~7비트까지의 레지스터 의미) */
	DDRG = 0x0F;		/* 포트 G의 0 ~ 3번째까지의 레지스터를 출력으로 사용 */
	DDRE = 0xFF;		/* 포트 E의 0 ~ 7번째까지의 모든 레지스터를 출력으로 사용 */
	
	EICRA = 0x0F;		/* 0~3비트까지 "1"로 두어 인터럽트 0, 1에서 상승 에지를 발생한다
						   (EICRA: Interrupt sense control 및 MCU의 일반적인 기능을 설정하는데 사용)
						 */
	
	EICRB = 0x00;
	
	EIMSK = 0x03;
	
	EIFR = 0x03;
	
	sei();
	
    while (1) 
    {
		PORTG = 0x07;
		PORTE = FND_DATA_TBL[time_100ms];
		_delay_ms(2);
		
		PORTG = 0x0D;
		PORTE = FND_DATA_TBL[time_1s];
		_delay_ms(3);
		
		PORTG = 0x0E;
		PORTE = FND_DATA_TBL[time_10s];
		_delay_ms(3);
		
		if(Time_Stop == 1){
			continue;
		}
		
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
	
	cli();
	time_10ms = 0;
	time_100ms = 0;
	time_1s = 0;
	time_10s = 0;
	
	sei();
	
}

ISR(INT1_vect){
	
	cli();
	if(Time_Stop == 0){
		Time_Stop = 1;
		}else{
		Time_Stop = 0;
		sei();
	}
	
}