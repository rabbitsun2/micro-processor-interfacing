#ifndef _JIHUN_
#define _JIHUN_

#include<avr/io.h>
#include<avr/interrupt.h>

typedef unsigned char  u08;
typedef   signed char  s08;
typedef unsigned short u16;
typedef   signed short s16;
typedef unsigned long  u32;
typedef   signed long  s32;
typedef unsigned long long u64;
typedef   signed long long s64;

#define TRUE	1	
#define FALSE	0

#define MAX_U08	255
#define MAX_U16	65535
#define MAX_U32	4294967295

// maximum values that can be held
// by signed data types (8,16,32bits)
#define MIN_S08	-128
#define MAX_S08	127
#define MIN_S16	-32768
#define MAX_S16	32767
#define MIN_S32	-2147483648
#define MAX_S32	2147483647

#ifndef outb
	#define	outb(addr, data)	addr = (data)
#endif
#ifndef inb
	#define	inb(addr)			(addr)
#endif
#ifndef BV
	#define BV(bit)			(1<<(bit))
#endif
#ifndef cbi
	#define cbi(reg,bit)	reg &= ~(BV(bit))
#endif
#ifndef sbi
	#define sbi(reg,bit)	reg |= (BV(bit))
#endif
#ifndef cli
	#define cli()			__asm__ __volatile__ ("cli" ::)
#endif
#ifndef sei
	#define sei()			__asm__ __volatile__ ("sei" ::)
#endif

#define MIN(a,b)			((a<b)?(a):(b))
#define MAX(a,b)			((a>b)?(a):(b))
#define ABS(x)				((x>0)?(x):(-x))

#define ARRAY_SIZE(array)	(sizeof(array)/sizeof(array[0]))

//#define read_XRAM(address)        (*(volatile unsigned char *)(0x8000+address))
//#define write_XRAM(address,value) ((*(volatile unsigned char *)(0x8000+address))=value)

//delay
#define CYCLES_PER_US ((F_CPU+500000)/1000000) 	// cpu cycles per microsecond
// CPU clock speed
//#define F_CPU        16000000               		// 16MHz processor
//#define F_CPU        14745000               		// 14.745MHz processor
//#define F_CPU        8000000               		// 8MHz processor
//#define F_CPU        7372800               		// 7.37MHz processor
//#define F_CPU        4000000               		// 4MHz processor
//#define F_CPU        3686400               		// 3.69MHz processor

//������ �迭 
void us_delay(unsigned short time_us);
void ms_delay(u16 time_ms);


// AIC23B SPI ���
void AIC23B_spi_write(u08 cntl,u08 data);

//normal SPI ���
void spi_write(u08 data);

//���� std�Լ�
u08 cal_bit_place(u08 bit);
//void uart_print(char *str);
void sprint_u16(u16 data, u08 * str); //u16�̳��� ������ ��Ʈ������ ��ȯ

void SPI_Init();

#endif
