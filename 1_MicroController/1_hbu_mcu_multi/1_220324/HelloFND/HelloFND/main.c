/*
 * HelloFND.c
 *
 * Created: 2022-03-23 15:00:19
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 		1. Hanback Microprocessor Kit (Atmega128)
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    
	unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
									0x6D, 0x7C, 0x07, 0x7F, 0x67, 
									0x77, 0x7C, 0x39, 0x5E, 0x79, 
									0x08, 0x80};
	unsigned char cnt = 0, i;
	
	DDRB = 0xFF;	// 二쇱냼 B: 0xFF 珥덇린�솕
	DDRD = 0xFF;	// 二쇱냼 D: 0xFF 珥덇린�솕
	
    while (1) 
    {
		PORTB = FND_DATA_TBL[cnt];
		PORTD = FND_DATA_TBL[cnt];
		
		cnt++;
		
		if(cnt > 17)
			cnt = 0;
			
		for(i = 0; i < 50; i++){
			_delay_ms(50);
		}
		
    }
	
	return 0;
	
}

