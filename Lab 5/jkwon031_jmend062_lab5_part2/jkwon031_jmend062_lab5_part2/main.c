/*
 * jkwon031_jmend062_lab5_part2.c
 *
 * Created: 1/27/2019 2:58:48 AM
 * Author : ericj
 */ 

#include <avr/io.h>

enum States{Start, Init, Waits0, Waits1, s0, s1, Both} state;

unsigned char tmpA1 = 0x00;
unsigned char tmpA2 = 0x00;
unsigned char tmpB = 0x00;

void Tick(){
	tmpA1 = ~PINA & 0x01;
	tmpA2 = ~PINA & 0x02;
	tmpB = PORTB;
	
	switch(state){
		case Start:
			tmpB = 0;
			state = Init;
			break;
		case Init:
			if(tmpA1 && tmpA2){
					state = Both;
			}else if(tmpA1){
					state = Waits0;
			}else if(tmpA2){
					state = Waits1;
			}else if(!tmpA1 && !tmpA2){
				state = Init;
			}
			break;
		case Waits0:
			if(tmpA2){
				state = Both;
				break;
			}else if(!tmpA1){
				state = s0;
			}
			break;
		case Waits1:
			if(tmpA1){
				state = Both;
				break;
			}
			if(!tmpA2){
				state = s1;
			}
			break;
		case s0:
			state = Init;
			break;
		case s1:
			state = Init;
			break;
		case Both:
			if(!tmpA1 && !tmpA2){
				state = Init;
			}else{
				state = Both;
			}
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
		case Waits0:
			break;
		case Waits1:
			break;
		case s0:
			if(tmpB < 9){
				tmpB++;
			}
			break;
		case s1:
			if(tmpB > 0){
				tmpB--;
			}
			break;
		case Both:
			tmpB = 0;
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