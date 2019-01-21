/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 3 Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab3_part4.c
 *
 * Created: 1/16/2019 7:46:08 PM
 * Author : ericj
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00; 
    /* Replace with your application code */
    while (1) 
    {
		tmpA = PINA;
		tmpB = (tmpB & 0xF0) | ((tmpA & 0xF0) >> 4);
		tmpC = (tmpC & 0x0F) | ((tmpA & 0x0F) << 4);
		
		PORTB = tmpB;
		PORTC = tmpC;
    }
}

