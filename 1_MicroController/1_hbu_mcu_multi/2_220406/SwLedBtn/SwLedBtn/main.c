/*
 * SwLedBtn.c
 *
 * Subject: FND Segment
 * Created: 2022-04-06 오전 9:25:57
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 
 */ 
#define F_CPU 1600000UL

#include <avr/io.h>
#include <util/delay.h>

int seq_led(int index);
int delay(int start, int end);

int main(void)
{
	
	unsigned int cnt = 0;

	DDRB = 0xFF;
	DDRD = 0xFF;
	
    while (1) 
    {
		seq_led(cnt);
		
		cnt++;
		
		if(cnt > 17){
			cnt = 0;
		}
		
		delay(0, 50);
		
    }
	
	return 0;
	
}

int seq_led(int index){
	
	unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07,
		0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71,
	0x08, 0x80};
	
	// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, b, C, d, E, F, _, .
	
	PORTB = FND_DATA_TBL[index];
	PORTD = FND_DATA_TBL[index];
	
}

int delay(int start, int end){

	for( start; start < end; start++ ){
		_delay_ms(100);
	}
	
}