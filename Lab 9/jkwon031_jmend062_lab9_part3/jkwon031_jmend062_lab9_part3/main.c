/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 9 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab9_part3.c
 *
 * Created: 2/10/2019 9:26:57 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "timer.h"


enum States {Init, OFF, PLAY, WAIT} state;
double melody[26] = { 261.63, 261.63 , 293.66, 261.63, 349.23, 329.63, 261.63, 261.63, 293.66, 261.63, 392.00, 349.23, 261.63, 261.63, 261.63, 440.00, 349.23, 349.23, 329.63, 293.66, 466.00, 466.00, 440.00, 349.23, 393.88, 349.23 };
unsigned char wait[25] = {0x02, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01};
unsigned char length[26] = { 0x01, 0x01, 0x04, 0x04, 0x04, 0x08, 0x01, 0x01, 0x04, 0x04, 0x04, 0x08, 0x01, 0x01, 0x04, 0x04, 0x02, 0x01, 0x04, 0x01, 0x01, 0x04, 0x04, 0x04, 0x08};
//double melody[5] = {392.00, 392.00, 440.00, 392.00, 261.63}
unsigned char count = 0x00;
unsigned char A0;
unsigned char done;
unsigned char number;
// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}

void tick(){
	A0 = ~PINA & 0x01;
	switch(state){
		case Init:
		state = OFF;
		break;
		
		case OFF:
		if(A0){
			done = 0x00;
			count = 0x00;
			number = 0x00;
			PWM_on();
			state = PLAY;
		}
		else {
			state = OFF;
		}
		break;
		
		case PLAY:
		if(!A0 && done == 0x01){
			PWM_off();
			state = OFF;
		}
		else if(A0 && done == 0x01){
			PWM_off();
			state = PLAY;
		}
		else if(!(!A0 && done == 0x01) && length[count] == number){
			number = 0x00;
			set_PWM(0);
			state = WAIT;
		}
		else {
			number = number + 1;
			state = PLAY;
		}
		break;
		
		case WAIT:
		if(wait[count] == number){
			number = 0x00;
			count = count + 1;
			if(count < 24){
				set_PWM(melody[count]);
			}
			else{
				done = 0x01;
			}
			state = PLAY;
		}
		else{
			number = number + 1;
			state = WAIT;
		}
		break;
	}
	switch(state){
		case Init:
		break;
		
		case OFF:
		break;
		
		case PLAY:
		break;
		
		case WAIT:
		break;
		
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(250);
	TimerOn();
	state = Init;
	while (1)
	{
		tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}

