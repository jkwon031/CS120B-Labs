/*
 * jkwon031_jmend062_lab6_part1.c
 *
 * Created: 1/29/2019 11:51:55 AM
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

enum States{Start, s0, s1, s2} state;

unsigned char tmpB = 0x00;

void Tick(){
	switch(state){
		case Start:
			state = s0;
			break;
		case s0:
			state = s1;
			break;
		case s1:
			state = s2;
			break;
		case s2:
			state = s0;
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
	TimerSet(1000);
	TimerOn();
	
    while (1) 
    {
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
    }
}

