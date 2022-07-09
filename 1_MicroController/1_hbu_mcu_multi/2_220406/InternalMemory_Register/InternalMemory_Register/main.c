/*
 * InternalMemory_Register.c
 *
 * Created: 2022-04-06 오전 10:03:18
 * Author : 정도윤(Doyun Jung)
 * Description:
 * 
 */ 

#define F_CPU 1600000UL
#include <avr/io.h>

unsigned char A = 0xAA;
unsigned char B = 0xBB;
unsigned char C = 0xCC;
unsigned char *ADD = 0x130;


int main(void)
{

	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRF = 0xFF;
	PORTF = 0x00;
	
	ADD = 0x140;
	*ADD = 0x11;
	*(ADD + 1) = 0x22;
	*(ADD + 2) = 0x33;
	*(ADD + 3) = 0x44;
	
	A = 0xBB;
	B = C - A;
	
	PORTA = A;
	PORTF = B;

    while (1) 
    {
		
    }
	
}