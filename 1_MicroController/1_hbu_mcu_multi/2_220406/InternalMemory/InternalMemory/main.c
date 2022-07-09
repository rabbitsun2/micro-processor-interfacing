/*
 * InternalMemory.c
 *
 * Created: 2022-04-06 오전 9:54:34
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 1. 내장 메모리를 살펴볼 수 있다.
 
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
		
		data << 1;
		
		for(i = 0; i < 1000; i++);
		
		if(data == 0x00)
			data = 0x01;
			
    }
	
	return 0;
	
}