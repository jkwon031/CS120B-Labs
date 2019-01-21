/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 3 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab3_part1.c
 *
 * Created: 1/15/2019 11:37:34 AM
 * Author : ericj
 */ 

#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	
	//unsigned char uc_buttonA = 0x00;
	//unsigned char uc_buttonB = 0x00;
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char bitNum = 8;
	unsigned char bitSize = 0x01;
	unsigned char uc_counter = 0;	
    while (1) 
    {
		tempA = PINA;
		tempB = PINB;
		uc_counter = 0;
		
		for(unsigned char i = 0; i < bitNum; i++){
			//uc_buttonA = tempA & bitSize;
			//uc_buttonB = tempB & bitSize;
	
			
			if(GetBit(tempA, i)){
				uc_counter++;
			}
			if(GetBit(tempB, i)){
				uc_counter++;
			}
			bitSize *= 0x02; 
		}
		PORTC = uc_counter;
    }
}

