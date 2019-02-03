/*
 * test_lab_7.c
 *
 * Created: 2/2/2019 8:40:56 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "io.c"
#include "timer.h"

enum States{Start, Init, Redo}state;
	
unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;

void Tick(){
	tmpA = ~PINA & 0x01;
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(tmpA){
				state = Redo;
			}else if(!tmpA){
				state = Init;
			}
			break;
		case Redo:
			if(tmpA){
				state = Init;
			}else if(!tmpA){
				state = Redo;
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
			tmpC = 0x00;
			break;
		case Redo:
			tmpC = 0x04;
			break;
		default:
			break;
	}
	LCD_Cursor(1);
	LCD_WriteData(tmpC + '0');
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    /* Replace with your application code */
	
	
	LCD_init();
	state = Start;
	tmpC = 0x00;
	TimerSet(1000);
	TimerOn();
	
	
	
    while (1) 
    {
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
    }
}

