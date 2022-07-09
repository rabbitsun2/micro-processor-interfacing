/*
 * Interrupt_LED.c
 *
 * Created: 2022-04-06 오전 10:26:24
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 
 */ 

#define F_CPU 1600000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char Time_STOP = 0;

ISR(INT0_vect);

int main(void)
{
	unsigned char LED_Data = 0x01;
	
	DDRD = 0xFE;	/* 포트 D의 0번째 레지스터를 사용하여 입력 
					   (0xFE는 1~7비트까지의 레지스터를 의미
					*/
	DDRE = 0xFF;	/* 포트 E의 0~7번째까지의 모든 레지스터를 출력으로 사용
					*/
	
	EICRA = 0x0F;	/* 0~3비트까지 "1"로 두어 인터럽트0에서 상승 에지를 발생한다. 
						(EICRA: Interrupt sense control및 MCU의 일반적인 기능을 설정하는 데 사용
					 */
	EICRB = 0x00;
	
	EIMSK = 0x01;	 /* 0비트가 "1"로 셋되고, 
						SREG 레지스터의 1비트가 "1"로 설정되어 있으면 외부인터럽트는 enable된다 */
	
	EIFR = 0x01;
	
	sei();
	
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
	
	cli();
	if(Time_STOP == 0){
		Time_STOP = 1;
	}
	else{
		Time_STOP = 0;
		sei();
	}
	
}