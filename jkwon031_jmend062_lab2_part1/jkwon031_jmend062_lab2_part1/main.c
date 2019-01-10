/*
 * jkwon031_jmend062_lab2_part1.c
 *
 * Created: 1/10/2019 11:38:48 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    
	unsigned char tempA1 = 0x00;
	unsigned char tempA2 = 0x00;
	unsigned char tempB = 0x00;
	while (1) 
    {
		tempA1 = PINA & 0x01; // PA0
		tempA2 = PINA & 0x02; // PA1
		
		if (tempA2 == 0x00 && tempA1 == 0x01){
			tempB = (tempB & 0xFC) | 0x01;
		}else{
			tempB = (tempB & 0xFC) | 0x00;
		}
		PORTB = tempB;
	}
	return 0;
}

