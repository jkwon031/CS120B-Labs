/*
 * jkwon031_jmend062_lab10_part3.c
 *
 * Created: 2/13/2019 11:47:55 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "timer.h"

enum BL_States{BL_SMStart, BL_On, BL_Off}BL_state;
enum TL_States{TL_SMStart, TL_S1, TL_S2, TL_S3}TL_state;
enum SP_States{SP_SMStart, SP_On, SP_Off}SP_state;
enum C_States{C_SMStart, C_Comb}C_state;
enum PC_States{PC_SMStart, PC_Up, PC_Down, PC_UpW, PC_DownW, PC_Base}PC_state;

unsigned char bled = 0x00;
unsigned char tled = 0x00;
unsigned char spin = 0x00;
unsigned char spout = 0x00;
unsigned char fcomb = 0x00;
unsigned char counter = 0x00;
unsigned char freq = 0x00;
unsigned char PA_0 = 0x00;
unsigned char PA_1 = 0x00;


/*// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_ frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0B = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 62500) { OCR0B = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR0B = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0B0 | (1 << WGM00));
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

*/

void PitchSwitch(){
	PA_0 = ~PINA & 0x01;
	PA_1 = ~PINA & 0x02;
	
	switch(PC_state){
		case PC_SMStart:
		PC_state = PC_Base;
		break;
		case PC_Base:
		if(PA_0){
			PC_state = PC_Up;
			}else if(PA_1){
			PC_state = PC_Down;
			}else{
			PC_state = PC_Base;
		}
		break;
		case PC_Up:
		if(PA_0){
			PC_state = PC_UpW;
			}else{
			PC_state = PC_Base;
		}
		break;
		case PC_Down:
		if(PA_1){
			PC_state = PC_DownW;
			}else{
			PC_state = PC_Base;
		}
		break;
		case PC_UpW:
		if(PA_0){
			PC_state = PC_UpW;
			}else{
			PC_state = PC_Base;
		}
		case PC_DownW:
		if(PA_1){
			PC_state = PC_DownW;
			}else{
			PC_state = PC_Base;
		}
		default:
		break;
	}
	switch(PC_state){
		case PC_SMStart:
		freq = 0x02;
		break;
		case PC_Base:
		break;
		case PC_Up:
		if(freq < 0x0A){
			freq++;
		}
		break;
		case PC_Down:
		if(freq > 0x01){
			freq--;
		}
		break;
		case PC_UpW:
		break;
		case PC_DownW:
		break;
		default:
		break;
	}
}
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
	//	PORTB = bled;
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
	//	PORTB = tled;
}

void Speaker(){
	spin = ~PINA;
	
	switch(SP_state){
		case SP_SMStart:
			SP_state = SP_Off;
			counter = 0x00;
			break;
		case SP_Off:
			if(spin == 0x04){
				if(counter <= freq){
					SP_state = SP_On;
					counter ++;
				}else if(counter >= freq){
					SP_state = SP_Off;
					counter = 0x00;
				}
			} else if(spin != 0x04){
				SP_state = SP_Off;
			}
			break;
		case SP_On:
			if(spin == 0x04){
				if(counter <= freq){
						SP_state = SP_On;
						counter ++;
					}else if(counter >= freq){
						SP_state = SP_Off;
						counter = 0x00;
						
				}
			}else if(spin != 0x04){
				SP_state = SP_Off;
			}
			break;
		default:
			SP_state = SP_SMStart;
			break;
	}
	switch(SP_state){
		case SP_SMStart:
			
			break;
		case SP_Off:
			spout = 0x00;
			break;
		case SP_On:
			spout = 0x10;
			break;	
	}
}

void CombineLED(){
	switch(C_state){
		case C_SMStart:
			C_state = C_Comb;
			break;
		case C_Comb:
			C_state = C_Comb;
			break;
		default:
			C_state = C_SMStart;
			break;
	}
	switch(C_state){
		case C_SMStart:
			break;
		case C_Comb:
			fcomb = bled | tled | spout;
			break;
		default:
			break;
	}
	PORTB = fcomb;
}

int main(void)
{
	unsigned long BL_elapsedTime = 0;
	unsigned long TL_elapsedTime = 0;
	unsigned long SP_elapsedTime = 0;
	const unsigned long timerPeriod = 1;
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	TimerSet(timerPeriod);
	TimerOn();
	BL_state = BL_SMStart;
	TL_state = TL_SMStart;
	SP_state = SP_SMStart;
	
	//PWM_on();
	
	/* Replace with your application code */
	while (1)
	{
		PitchSwitch();
		
		if(BL_elapsedTime >= 1000){
			BlinkLed();
			BL_elapsedTime = 0;
		}
		if(TL_elapsedTime >= 300){
			ThreeLeds();
			TL_elapsedTime = 0;
		}
		if(SP_elapsedTime >= 2){
			Speaker();
			SP_elapsedTime = 0;
		}
		
		
		CombineLED();
		
		while(!TimerFlag){}
		TimerFlag = 0;
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
		SP_elapsedTime += timerPeriod;
	}
}
