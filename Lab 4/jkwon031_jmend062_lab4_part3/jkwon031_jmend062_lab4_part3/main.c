/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 4 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab4_part3.c
 *
 * Created: 1/20/2019 1:03:09 PM
 * Author : ericj
 */ 

#include <avr/io.h>

enum States{Start, Lock, Wait, Unlock} state;

unsigned char tmpA1 = 0x00;
unsigned char tmpA2 = 0x00;
unsigned char tmpA7 = 0x00;
unsigned char tmpB = 0x00;

void Tick(){
	tmpA1 = PINA & 0x02;
	tmpA2 = PINA & 0x04;
	tmpA7 = PINA & 0x80;
	
	switch(state){
		case Start:
			state = Lock;
			break;
		case Lock:
			if(tmpA2){
				state = Wait;
			}else{
				state = Lock;
			}
			break;
		case Wait:
			if(!tmpA2 && tmpA1){
				state = Unlock;
			}else if(!tmpA2 && !tmpA1 || tmpA2 && !tmpA1){
				state = Wait;
			}else{
				state = Lock;
			}
			break;
		case Unlock:
			if(tmpA7){
				state = Lock;
			}else{
				state = Unlock;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			break;
		case Lock:
			tmpB = 0;
			break;
		case Wait:
			break;
		case Unlock:
			tmpB = 1;
			break;
		default:
			break;
	}
	PORTB = tmpB;
}

int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	tmpB = 0x00;
	state = Start;
	
    while (1) 
    {
		Tick();
    }
}

