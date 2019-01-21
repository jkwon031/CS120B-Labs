/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 3 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab3_part3.c
 *
 * Created: 1/16/2019 7:22:35 PM
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
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char fuel_level = 0x00;
	unsigned char tmpA = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		tmpA = PINA & 0x0F;
		
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
		
		tmpA = PINA & 0xF0;
		
		if((GetBit(tmpA, 4)) && (GetBit(tmpA, 5)) && (!GetBit(tmpA, 6))){
			fuel_level = SetBit(fuel_level, 7, 1);
		}else{
			fuel_level = SetBit(fuel_level, 7, 0);
		}
		PORTC = fuel_level;
    }
}

