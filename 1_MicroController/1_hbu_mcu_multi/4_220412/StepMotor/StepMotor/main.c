/*
 * StepMotor.c
 *
 * Created: 2022-04-12 오후 2:29:52
 * Author : 정도윤(Doyun Jung)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define S_MOTOR_DDR DDRC
#define S_MOTOR_DATA_OUT PORTC
#define S_MOTOR_PORT 0x0F
#define DIR_CHANHE_CNT 2	// 방향 전환 카운트
#define DIR_L 0
#define DIR_R 1

#define ON 0
#define OFF 1

unsigned char mot_cnt = 0, ecd_cnt = 0;
unsigned char dir = DIR_R;				// 처음방향은 우측부터
unsigned char flag = OFF;				// 채터링 방지
unsigned char flag_cnt = 0;

// 1-2 상 여자 값을 사용

unsigned char mot_tbl[] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};
	
ISR(INT0_vect);
ISR(TIMER0_OVF_vect);

int main(void)
{

	S_MOTOR_DDR |= S_MOTOR_PORT;
	
	EICRA = 0x02;
	EICRB = 0x00;
	EIMSK = 0x01;
	
	EIFR = 0x01;
	
	TCCR0 = 0x07;
	
	TCNT0 = 0xff - 160;
	TIMSK |= 1 << TOIE0;
	
	TIFR |= 1 << TOV0;
	sei();
	
    while (1);
	
	return 0;
}

ISR(INT0_vect){
	
	cli();
	
	flag = ON;
	if(ecd_cnt == DIR_CHANHE_CNT){
		dir = (dir == DIR_R ? DIR_L : DIR_R);
		ecd_cnt = 0;
	}
	
	sei();
	
}

ISR(TIMER0_OVF_vect){
	
	cli();
	TCNT0 = 0xff - 160;
	
	if(flag == ON){
		flag_cnt++;
	}
	
	if(flag_cnt == 10){
		flag = OFF;
		flag_cnt = 0;
		ecd_cnt++;
	}
	
	S_MOTOR_DATA_OUT = mot_tbl[mot_cnt];
	
	if(dir == DIR_R){
		if( mot_cnt++ == 7 ){
			mot_cnt = 0;
		}
	}
	else{
		
		if(mot_cnt-- == 0){
			mot_cnt = 7;
		}
		
		sei();
	}
	
}