/*
 * jkwon031_jmend062_lab2_part3.c
 *
 * Created: 1/10/2019 6:24:25 PM
 * Author : ericj
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	
	unsigned char cntavail = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpA2 = 0x00;
	unsigned char tmpA3 = 0x00;
	unsigned char tmpA4 = 0x00;
	unsigned char tmpA7 = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		cntavail = 0x00;
		tmpA1 = PINA & 0x01; //1
		tmpA2 = PINA & 0x02; //2
		tmpA3 = PINA & 0x04; //4
		tmpA4 = PINA & 0x08; //8
		tmpA7 = 0x40; //64
		
		
		if((tmpA1 != 0x01) && (tmpA2 != 0x02) && (tmpA3 != 0x04) && (tmpA4 != 0x08)){
			cntavail = (cntavail & 0xFC) | 0x04;
		}else if(((tmpA1 == 0x01) && (tmpA2 != 0x02) && (tmpA3 != 0x04) && (tmpA4 != 0x08)) ||
		((tmpA1 != 0x01) && (tmpA2 == 0x02) && (tmpA3 != 0x04) && (tmpA4 != 0x08)) ||
		((tmpA1 != 0x01) && (tmpA2 != 0x02) && (tmpA3 == 0x04) && (tmpA4 != 0x08)) || 
		((tmpA1 != 0x01) && (tmpA2 != 0x02) && (tmpA3 != 0x04) && (tmpA4 == 0x08))){
			cntavail = (cntavail & 0xFC) | 0x03;
		}else if(((tmpA1 == 0x01) && (tmpA2 == 0x02) && (tmpA3 != 0x04) && (tmpA4 != 0x08)) ||
		((tmpA1 == 0x01) && (tmpA2 != 0x02) && (tmpA3 == 0x04) && (tmpA4 != 0x08)) ||
		((tmpA1 == 0x01) && (tmpA2 != 0x02) && (tmpA3 != 0x04) && (tmpA4 == 0x08)) ||
		((tmpA1 != 0x01) && (tmpA2 == 0x02) && (tmpA3 == 0x04) && (tmpA4 != 0x08)) ||
		((tmpA1 != 0x01) && (tmpA2 == 0x02) && (tmpA3 != 0x04) && (tmpA4 == 0x08)) ||
		((tmpA1 != 0x01) && (tmpA2 != 0x02) && (tmpA3 == 0x04) && (tmpA4 == 0x08))){
			cntavail = (cntavail & 0xFC) | 0x02;
		}else if(((tmpA1 != 0x01) && (tmpA2 == 0x02) && (tmpA3 == 0x04) && (tmpA4 == 0x08)) ||
		((tmpA1 == 0x01) && (tmpA2 != 0x02) && (tmpA3 == 0x04) && (tmpA4 == 0x08)) ||
		((tmpA1 == 0x01) && (tmpA2 == 0x02) && (tmpA3 != 0x04) && (tmpA4 == 0x08)) ||
		((tmpA1 == 0x01) && (tmpA2 == 0x02) && (tmpA3 == 0x04) && (tmpA4 != 0x08))){
			cntavail = (cntavail & 0xFC) | 0x01;
		}else{
			cntavail = (cntavail & 0xFC) | 0x00;
		}
		if(cntavail == 0x00){
			PORTC = tmpA7;
		}else{
			PORTC = cntavail;
		}
	}
	return 0;
}