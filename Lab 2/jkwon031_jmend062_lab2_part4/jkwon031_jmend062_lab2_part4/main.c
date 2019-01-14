/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 2 Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon_jmend062_lab2_part4.c
 *
 * Created: 1/12/2019 2:45:28 PM
 * Author : ericj
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	MCUCR = 0x80;
	MCUCR = 0x80;
    DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char tmpD = 0x00; 
	unsigned char addABC = 0x00;
	unsigned char diffAC = 0x00;
	unsigned char diffCA = 0x00;
	while (1) 
    {
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PINC;
		addABC = tmpA + tmpB + tmpC;
		diffAC = tmpA - tmpC;
		diffCA = tmpC - tmpA;
		if (addABC > 0x8C)
		{
			tmpD = (tmpD & 0xFC) | 0x01;
		}
		if((diffAC > 0x50) || (diffCA > 0x50))
		{
			tmpD = tmpD + (tmpD & 0xFC) | 0x02;
		}
		PORTD = tmpD;
    }
	return 0;
}

