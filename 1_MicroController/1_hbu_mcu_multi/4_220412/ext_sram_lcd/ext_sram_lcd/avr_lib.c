#include"avr_lib.h"

void us_delay(unsigned short time_us){
	
	register u08 i;

	for(i=0; i < time_us ; i++){		//4 
		asm volatile("PUSH R0");		//2
		asm volatile("POP R0");			//2	 = 8cycle = 1.08us
									
	}

}
void ms_delay(u16 time_ms){
	register u16 i;

	for(i=0; i < time_ms ; i++){	
		us_delay(250);	
		us_delay(250);	
		us_delay(250);	
		us_delay(250);	// 1us * 1000 = 1ms
		
	}
}

//spi

void AIC23B_spi_write(u08 cntl,u08 data){
	

	SPDR = cntl;
	while((SPSR & 0x80)==0x00);
	PORTB	&=	~(0x01);

	SPDR	=	data;
	while((SPSR & 0x80)==0x00);
	PORTB	|=0x01;

	ms_delay(10);

}

void spi_write(u08 data){

	SPDR	=	data;
	while((SPSR & 0x80)==0x00);

}

u08 cal_bit_place(u08 bit){ //매개변수 bit 를 처음엔 char 형으로 했으나, 
							// 0x08 가 char 형으로는 	음수값으로 대처해버려 -0 으로 인식했었다.
							//그래서 unsigned char 형으로 변환 
	char i=1;

	while(1){
		if(bit>0x01)
			bit=bit>>1;
		else if(bit==0x01)
			return i;
		else
			return 0;

			i++;
	}
}

/*void uart_print(char *str){
	u08 i=0;
	while(str[i]!='\0')
		putch(str[i++]);
}*/

void sprint_u16(u16 data, u08 * str){
			
	if(data>10000){
		str[0] = (data/10000)+'0';
		str[1] = ((data/1000)%10)+'0';
		str[2] = ((data/100)%10)+'0';
		str[3] = ((data/10) %10 )+'0';	
		str[4] = (data%10)+'0';	
		str[5] = '\0';	
	}
	else if(data>1000){
		str[0] = (data/1000)+'0';
		str[1] = ((data/100)%10)+'0';
		str[2] = ((data/10)%10)+'0';
		str[3] = (data%10)+'0';	
		str[4] = '\0';	
	}
	else if(data>100){
		str[0] = (data/100)+'0';
		str[1] = ((data/10)%10)+'0';		
		str[2] = (data%10)+'0';	
		str[3] = '\0';	
	}
	else if(data>10){
		str[0] = ((data/10))+'0';
		str[1] = (data%10)+'0';	
		str[2] = '\0';	
	}
	else if(data>0){
		str[0] = (data)+'0';	
		str[1] = '\0';	
	}
	else	
		str[0] = '\0';	
}

void SPI_Init(){
	DDRB	|=	0x07; //우선 포트를 설정 miso 입력설정 
	PORTB	|=	0x01; // ~cs = 1 
	
	SPCR	=	0x50;
	SPSR	=	0x00;
}
