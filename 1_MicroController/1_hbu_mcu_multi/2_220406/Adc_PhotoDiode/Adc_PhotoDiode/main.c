/*
 * Adc_PhotoDiode.c
 *
 * Created: 2022-04-06 오후 2:18:28
 * Author : 정도윤(Doyun Jung)
 * Description: 
   1. ADC - PhotoDiode 센서의 값을 FND로 확인할 수 있다.
 */ 

#define F_CPU 1600000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum{C0, C1, C2, C3};

unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
								0x7C, 0x07, 0x7F, 0x67, 0x77, 0x7C,
								0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};

unsigned char lowValue = 0;
unsigned char highValue = 0;
unsigned int adcValue = 0;
unsigned char timer0Cnt = 0;

void print_FND(char selCx, unsigned char data);
ISR(TIMER0_OVF_vect);

int main(void)
{
	DDRE = 0xFF;		// 데이터 포트(Data Port)
	PORTE = 0x00;		// 0~7비트까지의 모든 비트를 클리어한다.
	
	DDRG = 0x0F;		/* Control port 0-3PIN 0~4비트까지의 register 중에서 0~3비트까지의
						   register를 사용하여 출력한다.
						*/
	PORTG = 0x0F;		/* 0~3비트까지의 비트를 1로 세트한다. */
	
	TCCR0 = 0x07;		/* Timer / Count0의 동작을 설정
							WGM0(1:0) = "00" 일반동작모드
							COM0(1:0) = "00" OC0 사용하지 않음
							CS0(2:0) = "111" Prescalar 1024분주 */
	
	TCNT0 = 0xff -80;	/* (1 / (7.3728Mhz / 1024 prescalar )) * 80 => 0.011s
						   0.011s를 얻기 위한 카운트값 */

	TIMSK |= 1 << TOIE0;	// 오버플로우 인터럽트
	TIFR |= 1 << TOV0;		// TOV0 Timer/Counter0 overflow flag 클리어
	
	ADMUX = 0xC0;			/* ADMUX 레지스터 중 6,7 번째 비트를 세트. 
								REFS(1:0) = "11"	internal 2.56V 전원 사용
								ADLAR = '0'   디폴트 우정렬
								MUX(4:0)="00000"    ADC0 핀사용 단극성 입력 사용
							*/
	
	ADCSR = 0xA6;
	
	ADCSR |= 0x40;
	
	sei();
	
    while (1) 
    {
		print_FND(C0, adcValue % 10);			// 1의 자리
		_delay_ms(3);
		
		print_FND(C1, (adcValue / 10) % 10);	// FND [1~9까지 표시], A,b,C,D,E,f 표시 안 됨
		_delay_ms(3);
		
		print_FND(C2, adcValue / 100);			// 100의 자리 표시
		_delay_ms(3);
		
    }
	
}

ISR(TIMER0_OVF_vect){
	
	cli();
	TCNT0 = 0xff - 80;
	timer0Cnt++;
	
	if(timer0Cnt == 90){		// 0.011s * 90 = 1s (1초를 얻기 위한 카운트 횟수)
		
		timer0Cnt = 0;
		
		while ( (ADCSR&0x10) == 0x00);	// ADC 변환이 끝날 때까지 대기
		
		lowValue = ADCL;
		highValue = ADCH;
		
		adcValue = (highValue << 8) | lowValue;
		
	}
	
	sei();
	
}

void print_FND(char selCx, unsigned char data){
	
	switch(selCx){
		
		case C3:
			PORTG &= 0xF0;	// 하나씩만 입력하기 위해서 그 전의 내용을 초기화 시킴.
			PORTG |= 0x0E;	// 포트 G의 G0을 사용하여 C3로 출력
			
			break;
			
		case C2:
			PORTG &= 0xF0;	// 하나씩만 입력하기 위해서 그 전의 내용을 초기화 시킴.
			PORTG |= 0x0D;	// 포트 G의 G1을 사용하여 C2로 출력
			
			break;
			
		case C1:
			PORTG &= 0xF0;	// 하나씩만 입력하기 위해서 그 전의 내용을 초기화 시킴.
			PORTG |= 0x0B;	// 포트 G의 G2을 사용하여 C1로 출력
			
			break;
			
		case C0:
			PORTG &= 0xF0;	// 하나씩만 입력하기 위해서 그 전의 내용을 초기화 시킴.
			PORTG |= 0x07;	// 포트 G의 G3을 사용하여 C0로 출력
			
			break;
			
		default:
			PORTG &= 0xF0;	// 하나씩만 입력하기 위해서 그 전의 내용을 초기화 시킴.
			PORTG |= 0x0F;	// 포트 G의 G4를 사용하지 않는다
			
			break;
	}
	
	PORTE = FND_DATA_TBL[data];
	
}