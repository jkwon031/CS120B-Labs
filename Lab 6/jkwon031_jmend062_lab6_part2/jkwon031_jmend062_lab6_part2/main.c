/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 6 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab6_part2.c
 *
 * Created: 1/29/2019 12:27:01 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "timer.h"
// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

enum States{Start, s0, s1, s2, s3, pause_s0, pause_s1, pause_s2, pause_s3} state;

unsigned char tmpB = 0x00;

void Tick(){
	unsigned char tmpA = ~PINA & 0x01;
	switch(state){
		case Start:
			state = s0;
			break;
		case s0:
			if(!tmpA){
				state = s1;
			}else if(tmpA){
				state = pause_s0;
			}
			break;
		case s1:
			if(!tmpA){
				state = s2;
			}else if(tmpA){
				state = pause_s1;
			}
			break;
		case s2:
			if(!tmpA){
				state = s3;
			}else if(tmpA){
				state = pause_s2;
			}
			break;
		case s3:
			if(!tmpA){
				state = s0;
			}else if(tmpA){
				state = pause_s3;
			}
			break;
		case pause_s0:
			if(tmpA){
				state = s0;
			}else if(!tmpA){
				state = pause_s0;				
			}
			break;
		case pause_s1:
			if(tmpA){
				state = s0;
			}else if(!tmpA){
				state = pause_s1;
			}
			break;
		case pause_s2:
			if(tmpA){
				state = s0;
			}else if(!tmpA){
				state = pause_s2;
			}
			break;
		case pause_s3:
			if(tmpA){
				state = s0;
			}else if(!tmpA){
				state = pause_s3;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			break;
		case s0:
			tmpB = 0x01;
			break;
		case s1:
			tmpB = 0x02;
			break;
		case s2:
			tmpB = 0x04;
			break;
		case s3:
			tmpB = 0x02;
			break;
		case pause_s0:
			break;
		case pause_s1:
			break;
		case pause_s2:
			break;
		case pause_s3:
			break;
		default:
			break;
	}
	PORTB = tmpB;
}

int main(void)
{
	/* Replace with your application code */
	tmpB = 0x00;
	state = Start;
	TimerSet(300);
	TimerOn();
	
	DDRA = 0x00; PORTA = 0xFF;
	
	while (1)
	{
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}



