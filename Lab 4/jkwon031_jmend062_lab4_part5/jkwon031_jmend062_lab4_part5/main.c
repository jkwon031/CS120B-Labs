/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 4 Exercise # 5
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
/*
 * jkwon031_jmend062_lab4_part5.c
 *
 * Created: 1/20/2019 4:33:26 PM
 * Author : ericj
 */ 

#include <avr/io.h>

enum States{Start, RESET, WaitL1, WaitL2, WaitL3, Flip} state;

unsigned char tmpA1 = 0x00;
unsigned char tmpA2 = 0x00;
unsigned char tmpA3 = 0x00;
unsigned char tmpA4 = 0x00;
unsigned char tmpA7 = 0x00;
unsigned char tmpB = 0x00;


void Tick(){
	unsigned char arr[4] = {0x04, 0x01, 0x02, 0x01};
	tmpA1 = PINA & arr[0];
	tmpA2 = PINA & arr[1];
	tmpA3 = PINA & arr[2];
	tmpA4 = PINA & arr[3];
	tmpA7 = PINA & 0x80;
		
	switch(state){
		case Start:
			state = RESET;
			break;
		case RESET:
			if(tmpA7 && tmpB){
				state = Flip;
			}else if(tmpA1){
				state = WaitL1;
			}else{
				state = RESET;
			}
			break;
		case WaitL1:
			if(!tmpA1 && tmpA2){
				state = WaitL2;
			}else if((!tmpA1 && !tmpA2) || (tmpA1 && !tmpA2)){
				state = WaitL1;
			}else{
				state = RESET;
			}
			break;
		case WaitL2:
			if(!tmpA2 && tmpA3){
				state = WaitL3;
			}else if((!tmpA2 && !tmpA3) || (tmpA2 && !tmpA3)){
				state = WaitL2;
			}else{
				state = RESET;
			}
			break;
		case WaitL3:
			if(!tmpA3 && tmpA4){
				state = Flip;
			}else if((!tmpA3 && !tmpA4) || (tmpA3 && !tmpA4)){
				state = WaitL3;
			}else{
				state = RESET;
			}
			break;
		case Flip:
			state = RESET;
			break;
		default:
			state = Start;
			break;
	}
	switch(state){
		case Start:
			break;
		case WaitL1:
			break;
		case WaitL2:
			break;
		case WaitL3:
			break;
		case Flip:
			if(!tmpB){
				tmpB = 1;
			}else if(tmpB){
				tmpB = 0;
			}
			break;
		case RESET:
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


