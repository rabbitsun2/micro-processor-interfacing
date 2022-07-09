/*
 * HelloSwLED.c
 *
 * Created: 2022-03-23 14:53:19
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 		1. Hanback Microprocessor Kit (Atmega128)
 */ 

#include <avr/io.h>


int main(void)
{
	
	DDRC = 0xFF;
	DDRD = 0x00;
	
    while (1) 
    {
		PORTC = PIND;
	}
	
	return 0;
	
}

