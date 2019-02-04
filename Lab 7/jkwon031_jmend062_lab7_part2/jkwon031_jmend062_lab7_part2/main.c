/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 7 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab7_part2.c
 *
 * Created: 2/2/2019 10:54:45 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "io.c"
#include "timer.h"

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

enum States{Start, s0, s1, s2, s3, pause_s0, pause_s1, pause_s2, pause_s3, Win} state;

unsigned char tmpB = 0x00;
unsigned char count = 0x05;

void Tick(){
	unsigned char tmpA = ~PINA & 0x01;
	switch(state){
		case Start:
			count = 5;
			state = s0;
			LCD_ClearScreen();
			LCD_Cursor(1);
			LCD_WriteData(count + '0');			
			break;
		case s0:
			if(!tmpA){
				state = s1;
			}else if(tmpA && count > 0){
				state = pause_s0;
				count--;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_WriteData(count + '0');	
			}else if(tmpA && count == 0){
				state = pause_s0;
				count = 0;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_WriteData(count + '0');	
			}
			break;
		case s1:
			if(!tmpA){
				state = s2;
			}else if(tmpA && count < 8){
				state = pause_s1;
				count++;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_WriteData(count + '0');	
			}else if(tmpA && count == 8){
				count++;
				state = Win;
			}
			break;
		case s2:
			if(!tmpA){
				state = s3;
			}else if(tmpA && count > 0){
				state = pause_s2;
				count--;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_WriteData(count + '0');	
			}else if(tmpA && count == 0){
				state = pause_s2;
				count = 0;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_WriteData(count + '0');	
			}
			break;
		case s3:
			if(!tmpA){
				state = s0;
			}else if(tmpA && count < 8){
				state = pause_s3;
				count++;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_WriteData(count + '0');	
			}else if(tmpA && count == 8){
				count++;
				state = Win;
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
		case Win:
			if(tmpA){
				state = Start;
			}else if(!tmpA){
				state = Win;
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
		case Win:
			LCD_ClearScreen();
			LCD_DisplayString(1, "Winner");
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
		DDRB = 0xFF; PORTB = 0x00;
		DDRC = 0xFF; PORTC = 0x00;
		DDRD = 0xFF; PORTD = 0x00;
		
		count = 0x05;
		
		LCD_init();		
		
		while (1)
		{
			Tick();
			while(!TimerFlag){}
			TimerFlag = 0;
		}
}

