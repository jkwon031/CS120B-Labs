/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 3 Exercise # 5
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab3_part5.c
 *
 * Created: 1/16/2019 8:14:19 PM
 * Author : ericj
 */ 

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
	DDRB = 0x00; PORTB = 0xFF;
	DDRD = 0x00; PORTD = 0xFF;
	
	unsigned short weight = 0x0000;
	unsigned char tmpB = 0x00;
	unsigned char tmpD = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		tmpB = PINB;
		tmpD = PIND;
		
		weight = tmpD;
		//weight = weight << 1;
		
		if(GetBit(tmpB, 0)){
			weight++;
		}
		
		if(weight >= 70){
			SetBit(tmpB, 1, 1);
		}
		if(weight > 5 && weight < 70){
			SetBit(tmpB, 2, 1);
		}
		PORTB = tmpB;
    }
}

