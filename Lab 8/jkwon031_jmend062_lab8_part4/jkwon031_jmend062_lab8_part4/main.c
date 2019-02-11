/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 8 Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab8_part4.c
 *
 * Created: 2/7/2019 12:19:14 PM
 * Author : ericj
 */ 

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
	ADC_init();
	while (1)
	{
		DDRA = 0x00; PORTA = 0xFF ;
		DDRB = 0xFF; PORTB = 0x00;
		
		unsigned short A = ADC;
		unsigned char B;
		
		if (A >= 0x93){
			B = 0xFF;
		}
		else if (A < 0x93 && A >= 0x87){
			B = 0x7F;
		}
		else if (A < 0x87 && A >= 0x7B){
			B = 0x3F;
		}
		else if (A < 0x7B && A >= 0x6F){
			B = 0x1F;
		}
		else if (A < 0x6F && A >= 0x63){
			B = 0x0F;
		}
		else if (A < 0x63 && A >= 0x57){
			B = 0x07;
		}
		else if (A < 0x57 && A >= 0x4B){
			B = 0x03;
		}
		else{
			B = 0x01;
		}
		
		PORTB = B;
		
	}
}

