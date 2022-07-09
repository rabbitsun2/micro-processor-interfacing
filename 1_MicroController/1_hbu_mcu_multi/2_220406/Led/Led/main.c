/*
 * Led.c
 *
 * Created: 2022-04-06 오전 9:17:07
 * Author : 정도윤(Doyun Jung)
 */ 

#include <avr/io.h>
#include <util/delay.h>

int delay(int i, int end);

int main(void)
{
	int i;
	unsigned char LED_Data = 0x00;
	
    DDRE = 0xFF;
	
    while (1) 
    {
		PORTE = LED_Data;
		LED_Data++;
		
		delay(0, 100);
		
    }
	
	return 0;
	
}

int delay(int i, int end){
	
	for(i; i < end; i++){
		_delay_ms(100);
	}
	
}