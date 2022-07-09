/*
 * TimerAndPwm.c
 * 예제명: LED 밝기 조절 프로젝트
 * Created: 2022-04-06 오후 12:57:10
 * Author : 정도윤(Doyun Jung)
 
 * PWM: Pulse Width Modulation(펄스 폭 변조)
   펄스란 짧은 시간동안 생기는 진동 현상과 같은 것
   평상시 0이란 값으로 있다가 짧은 시간 1의 값을 가지는 경우를 생각하면 된다.
 
 */ 

#define F_CPU 1600000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void turnOn(char Light){
	
	// OCR0 값을 조절하여 밝기 조절함.
	for (Light = 0; Light < 255; Light++){
		OCR0 = Light;
		_delay_ms(10);
	}
	
}

void turnOff(char Light){
	
	// OCR0 값을 조절하여 밝기 조절함.
	for (Light = 255; 0 < Light; Light--){
		OCR0 = Light;
		_delay_ms(10);
	}
	
}

int main(void)
{
    unsigned char Light = 0;
	
	DDRB = 0x10;	// 0~7비트까지의 레지스터 중에서 4번째 비트의 레지스터를 사용하여 출력한다.
	
	TCCR0 = 0x71;	// PWM, No Prescaling
	
	TCNT0 = 0;		// 레지스터 클리어
	
    while (1) 
    {
		turnOn(Light);
		turnOff(Light);
    }
	
	return 0;
}

