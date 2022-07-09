/*
 * ExampleDebug.c
 *
 * Created: 2022-03-23 15:10:58
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 		1. Hanback Microprocessor Kit (Atmega128)
 * 		2. Microchip Studio 7에서 Simulator 모드로 디버그를 수행하였음.
 */ 

#include <avr/io.h>


int main(void)
{
	unsigned char data = 0x01;
	unsigned long i;
	
	DDRA = 0xFF;
	
	PORTA = 0x00;
	
    while (1) 
    {
		PORTA = data;
		
		data <<= i;
		
		for(i = 0; i < 1000; i++);
		
		if(data == 0x00)
			data = 0x01;
		
    }
	
	return 0;
	
}

