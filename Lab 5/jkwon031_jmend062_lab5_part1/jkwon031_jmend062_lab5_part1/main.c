/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 5 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
/*
 * jkwon031_jmend062_lab5_part1.c
 *
 * Created: 1/24/2019 12:04:44 PM
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char fuel_level = 0x00;
	unsigned char tmpA = 0x00;
	/* Replace with your application code */
	while (1)
	{
		tmpA = ~PINA;
		
		if (tmpA > 0x00){
			fuel_level = SetBit(fuel_level, 5, 1);
		}else{
			fuel_level = SetBit(fuel_level, 5, 0);
		}
		if(tmpA > 0x02){
			fuel_level = SetBit(fuel_level, 4, 1);
		}else{
			fuel_level = SetBit(fuel_level, 4, 0);
		}
		if(tmpA > 0x04){
			fuel_level = SetBit(fuel_level, 3, 1);
		}else{
			fuel_level = SetBit(fuel_level, 3, 0);
		}
		if(tmpA > 0x06){
			fuel_level = SetBit(fuel_level, 2, 1);
		}else{
			fuel_level = SetBit(fuel_level, 2, 0);
		}
		if(tmpA > 0x09){
			fuel_level = SetBit(fuel_level, 1, 1);
		}else{
			fuel_level = SetBit(fuel_level, 1, 0);
		}
		if(tmpA > 0x0C){
			fuel_level = SetBit(fuel_level, 0, 1);
		}else{
			fuel_level = SetBit(fuel_level, 0, 0);
		}
		if(tmpA <= 4){
			fuel_level = SetBit(fuel_level, 6, 1);
		}else{
			fuel_level = SetBit(fuel_level, 6, 0);
		}
		PORTB = fuel_level;
	}
}

