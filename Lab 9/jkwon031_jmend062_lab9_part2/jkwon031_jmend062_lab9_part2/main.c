/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 9 Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

/*
 * jkwon031_jmend062_lab9_part2.c
 *
 * Created: 2/10/2019 2:58:25 PM
 * Author : ericj
 */ 

#include <avr/io.h>

enum States {Init, OFF, WAIT, UP, DOWN, STAY, WAIT_ON, WAIT_OFF }state;

double scale[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

unsigned char A0;
unsigned char A1;
unsigned char tmpA2;
unsigned char count;

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
	TCCR0A = (1 << COM0A0) | (1 << WGM00);
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
	A1 = ~PINA & 0x02;
	tmpA2 = ~PINA & 0x04;
	
	switch(state){
		case Init:
		state = OFF;
		break;
		
		case OFF:
		if(A0){
			state = WAIT_ON;
		}
		else{
			state = OFF;
		}
		break;
		
		case WAIT_ON:
		if(A0){
			state = WAIT_ON;
		}
		else{
			state = STAY;
		}
		break;
		
		case STAY:
		if(!A0 && !A1 && !tmpA2){
			state = STAY;
		}
		else if(A0 && !A1 && !tmpA2){
			state = WAIT_OFF;
		}
		else if(!A0 && A1 && !tmpA2){
			state = UP;
		}
		else if(!A0 && !A1 && tmpA2){
			state = DOWN;
		}
		else{
			state = STAY;
		}
		break;
		
		case UP:
		if(A1){
			state = WAIT;
		}
		else{
			state = STAY;
		}
		break;
		
		case DOWN:
		if(tmpA2){
			state = WAIT;
		}
		else{
			state = STAY;
		}
		break;
		
		case WAIT:
		if(!A0 && !A1 && !tmpA2){
			state = STAY;
		}
		else{
			state = WAIT;
		}
		break;
		
		case WAIT_OFF:
		if(A0){
			state = WAIT_OFF;
		}
		else{
			state = OFF;
		}
		break;
	}
	switch(state){
		case OFF:
		PWM_off();
		break;
		
		case WAIT_OFF:
		PWM_off();
		break;
		
		case WAIT_ON:
		PWM_on();
		count = 0x00;
		set_PWM(scale[count]);
		break;
		
		case UP:
		if(count <= 0x06){
			count = count + 1;
		}
		set_PWM(scale[count]);
		break;
		
		case STAY:
		break;
		
		case DOWN:
		if(count >= 0x01){
			count = count - 1;
		}
		set_PWM(scale[count]);
		break;
		
		case WAIT:
		break;
		
		case Init:
		count = 0x00;
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	PWM_off();
	state = Init;
	
	while (1)
	{
		tick();
	}
}


