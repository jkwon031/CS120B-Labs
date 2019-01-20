/*
 * jkwon031_jmend062_lab4_part1.c
 *
 * Created: 1/17/2019 11:25:09 AM
 * Author : ericj
 */ 

#include <avr/io.h>

enum States{Start, s0, s1} state;

unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void Tick(){
	tmpA = PINA & 0x01;

	switch (state){
		case Start:
			state = s0;
			break;
		case s0:
			if(tmpA){
				state = s1;
			}else if (!tmpA){
				state = s0;
			}
			break;
		case s1:
			if(tmpA){
				state = s0;
			}else if(!tmpA){
				state = s1;
			}
			break;
		default:
			state = Start;
			break;
	}
	
	switch (state){
		case Start:
			break;
		case s0:
			tmpB = 0x01;
			break;
		case s1:
			tmpB = 0x02;
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

