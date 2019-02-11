/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 8 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab8_part2.c
 *
 * Created: 2/7/2019 11:56:38 AM
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	/* Replace with your application code */
	unsigned short ADC_result = 0x0000;
	unsigned char tmpB = 0x00;
	unsigned char tmpD = 0x00;
	
	ADC_init();
	
	while (1)
	{
		ADC_result = ADC;
		tmpB = (char)ADC_result;
		tmpD = (char)(ADC_result >> 8);
		
		PORTB = tmpB;
		PORTD = tmpD;
	}
}


