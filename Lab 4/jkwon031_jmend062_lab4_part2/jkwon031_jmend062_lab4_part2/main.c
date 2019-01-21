/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 4 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab4_part2.c
 *
 * Created: 1/20/2019 12:12:21 AM
 * Author : ericj
 */ 

#include <avr/io.h>

enum States{Start, Init, s0, s1, Both} state;

unsigned char tmpA1 = 0x00;
unsigned char tmpA2 = 0x00;
unsigned char tmpC = 0x00;

void Tick(){
	tmpA1 = PINA & 0x01;
	tmpA2 = PINA & 0x02;
	tmpC = PORTC;
	
	switch(state){
		case Start:
			tmpC = 7;
			state = Init;
			break;
		case Init:
			if(tmpA1 && !tmpA2){
				state = s0;
			}else if(!tmpA1 && tmpA2){
				state = s1;
			}else if(tmpA1 && tmpA2){
				state = Both;
			}else if(!tmpA1 && !tmpA2){
				state = Init;
			}
			break;
		case s0:
			state = Init;
			break;
		case s1:
			state = Init;
			break;
		case Both:
			state = Init;
			break;
		default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			break;
		case Init:
			break;
		case s0:
			if(tmpC < 9){
				tmpC++;
			}
			break;
		case s1:
			if(tmpC > 0){
				tmpC--;
			}
			break;
		case Both:
			tmpC = 0;
		default:
			break;
	}
	PORTC = tmpC;
}


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	tmpC = 0x00;
	state = Start;
    while (1) 
    {
		Tick();
    }
}

