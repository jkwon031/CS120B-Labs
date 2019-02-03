/*
 * jkwon031_jmend062_lab7_part1.c
 *
 * Created: 2/2/2019 5:42:42 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "io.c"
#include "timer.h"

enum States{Start, Init, Waits0, Waits1, s0, s1, Both} state;

unsigned char tmpA1 = 0x00;
unsigned char tmpA2 = 0x00;
unsigned char tmpC = 0x00;

void Tick(){
	tmpA1 = ~PINA & 0x01;
	tmpA2 = ~PINA & 0x02;
	//tmpC = 0x00;
	
	switch(state){
		case Start:
			tmpC = 0;
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
			}else/* if(!tmpA1)*/{
				state = s0;
			}
			break;
		case Waits1:
			if(tmpA1){
				state = Both;
				break;
			}else /*if(!tmpA2)*/{
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
			break;
		default:
			break;
	}
	LCD_Cursor(1);
	LCD_WriteData(tmpC + '0');
}

int main(void)
{
	/* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	tmpC = 0x00;
	state = Start;
	LCD_init();
	
	TimerSet(300);
	TimerOn();
	
	while (1)
	{
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}



