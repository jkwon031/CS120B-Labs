/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 10 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab10_part1.c
 *
 * Created: 2/12/2019 11:57:27 AM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "timer.h"

enum BL_States{BL_SMStart, BL_On, BL_Off}BL_state;
enum TL_States{TL_SMStart, TL_S1, TL_S2, TL_S3}TL_state;
enum C_States{C_SMStart, C_Comb}C_state;
	
unsigned char bled = 0x00;
unsigned char tled = 0x00;
unsigned char fcomb = 0x00;

void BlinkLed(){
	switch(BL_state){
		case BL_SMStart:
			BL_state = BL_On;
			break;
		case BL_On:
			BL_state = BL_Off;
			break;
		case BL_Off:
			BL_state = BL_On;
			break;
		default:
			BL_state = BL_SMStart;
			break;
	}
	switch(BL_state){
		case BL_SMStart:
			break;
		case BL_On:
			bled = 0x08;
			break;
		case BL_Off:
			bled = 0x00;
			break;
		default:
			break;
	}
}

void ThreeLeds(){
	switch(TL_state){
		case TL_SMStart:
			TL_state = TL_S1;
			break;
		case TL_S1:
			TL_state = TL_S2;
			break;
		case TL_S2:
			TL_state = TL_S3;
			break;
		case TL_S3:
			TL_state = TL_S1;
			break;
		default:
			TL_state = TL_SMStart;
			break;
	}
	switch(TL_state){
		case TL_SMStart:
			break;
		case TL_S1:
			tled = 0x01;
			break;
		case TL_S2:
			tled = 0x02;
			break;
		case TL_S3:
			tled = 0x04;
			break;
		default:
			break;
	}
}

void CombineLED(){
	switch(C_state){
		case C_SMStart:
			C_state = C_Comb;
		case C_Comb:
			C_state = C_Comb;
			break;
		default:
			C_state = C_SMStart; 
	}
	switch(C_state){
		case C_SMStart:
			break;
		case C_Comb:
			BlinkLed();
			ThreeLeds();
			fcomb = bled | tled;
			break;
		default:
			break;
	}
	PORTB = fcomb;
}

int main(void)
{	
	//DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	fcomb = 0;
	TimerSet(1000);
	TimerOn();
	BL_state = BL_SMStart;
	TL_state = TL_SMStart;
	
    /* Replace with your application code */
    while (1) 
    {
		CombineLED();
				
		while(!TimerFlag){}
		TimerFlag = 0;		
    }
}

