/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 10 Exercise # 5
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab10_part5.c
 *
 * Created: 2/17/2019 10:59:28 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "timer.h"

unsigned char tmpA0 = 0x00;
unsigned char tmpA1 = 0x00;
unsigned char tmpB = 0x00;
unsigned short i = 0x00;
unsigned char increase = 0x00;
unsigned char ws = 0x00;
unsigned char wf = 0x00;

enum States { Start, Initial, Wait_I, Wait_D, Increment, Decrement, Reset } state;

void Tick() {
	
	tmpA0 = ~PINA & 0x01;
	tmpA1 = ~PINA & 0x02;
	
	switch(state) {
		case Start:
			state = Initial;
			break;
		case Initial:
			if (tmpA0 && !tmpA1){
				state = Wait_I;
			}
			if (!tmpA0 && tmpA1){
				state = Wait_D;
			}
			if (tmpA0 && tmpA1){
				state = Reset;
			}
			break;
		case Wait_I:
			if (!tmpA0){
				state = Increment;
			}
			if (tmpA0){
				i++;
				if(ws && i == 0x0F){
					ws = 0x00;
					wf = 0x01;
					state = Increment;
				}else if(ws && i % 0x05 == 0x00){
					state = Increment;
				}else if(wf && i % 0x02 == 0x00){
					state = Increment;
				}
			}
			if (tmpA0 && tmpA1){
				state = Reset;
			}
			break;
		case Increment:
			if(tmpA0){
				state = Wait_I;
			}else{
				state = Initial;
			}
			break;
		case Wait_D:
			if (!tmpA1){
				state = Decrement;
			}else if (tmpA1){
				i++;
				if(ws && i == 0x0F){
					ws = 0x00;
					wf = 0x01;
					state = Decrement;
				}
				if(ws && i % 0x05 == 0x00) {
					state = Decrement;
				}
				if(wf && i % 0x02 == 0x00) {
					state = Decrement;
				}
			}else if (tmpA0 && tmpA1){
				state = Reset;
			}
			break;
		case Decrement:
			if(tmpA1){
				state = Wait_D;
			}else{
				state = Initial;
			}
			break;
		case Reset:
			if (!tmpA0 && !tmpA1){
				state = Initial;
			}
			break;
		default:
			state = Start;
			break;
	}
	
	switch(state) {
		case Start:
			break;
		case Initial:
			ws = 0x01;
			wf = 0x00;
			i = 0;
			break;
		case Wait_I:
			break;
		case Increment:
			if(tmpB < 0x09){
				tmpB = tmpB + 0x01;
			}
			break;
		case Wait_D:
			break;
		case Decrement:
			if(tmpB > 0x00){
				tmpB = tmpB - 0x01;
			}
			break;
		case Reset:
			tmpB = 0x00;
			break;
		default:
			break;
	}
	PORTB = tmpB;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Start;
	TimerSet(200);
	TimerOn();
	
	while (1) {
		Tick();
		while (!TimerFlag) {} // Wait for timer period
		TimerFlag = 0; // Lower flag raised by timer
	}
}

