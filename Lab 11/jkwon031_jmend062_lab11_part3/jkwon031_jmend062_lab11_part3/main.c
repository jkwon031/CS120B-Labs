/*
 * jkwon031_jmend062_lab11_part3.c
 *
 * Created: 2/24/2019 10:38:24 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"
#include "io.c"
#include <stdio.h>

unsigned char GetKeypadKey() {

	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('1'); }
	if (GetBit(PINC,1)==0) { return('4'); }
	if (GetBit(PINC,2)==0) { return('7'); }
	if (GetBit(PINC,3)==0) { return('*'); }

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('2'); }
	if (GetBit(PINC,1)==0) { return('5'); }
	if (GetBit(PINC,2)==0) { return('8'); }
	if (GetBit(PINC,3)==0) { return('0'); }
	// ... *****FINISH*****

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('3'); }
	if (GetBit(PINC,1)==0) { return('6'); }
	if (GetBit(PINC,2)==0) { return('9'); }
	if (GetBit(PINC,3)==0) { return('#'); }
	// ... *****FINISH*****

	// Check keys in col 4
	PORTC = 0x7F; // Enable col 7 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('A'); }
	if (GetBit(PINC,1)==0) { return('B'); }
	if (GetBit(PINC,2)==0) { return('C'); }
	if (GetBit(PINC,3)==0) { return('D'); }
	// ... *****FINISH*****

	return('\0'); // default value

}

//--------Find GCD function --------------------------------------------------
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
b = c;
	}
	return 0;
}
//--------End find GCD function ----------------------------------------------

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;

//--------End Task scheduler data structure-----------------------------------

//--------Shared Variables----------------------------------------------------
unsigned char SM1_output[] = " ";
unsigned char i = 0;
unsigned char all_string[] = "                CS120B is Legend... wait for it DARY!                ";
unsigned char SM2_output[] = "                ";
//unsigned char SM3_output = 0x00;
//unsigned char pause = 0;

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum SM1_States {SM1_input};

// Monitors button connected to PA0. 
// When button is pressed, shared variable "pause" is toggled.
int SMTick1(int state) {

	// Local Variables
	unsigned char x; 
	switch (state){
		
	case SM1_input:
	state = SM1_input;
	break;
	
	default:
	state = SM1_input;
	break;
	
	}
	
	switch(state){
		
	case SM1_input:
	 x = GetKeypadKey();
	 switch (x) {
		 case '\0': SM1_output[0] = SM1_output[0]; break; // All 5 LEDs on
		 case '1': SM1_output[0] = '1';  break; // hex equivalent
		 case '2': SM1_output[0] = '2';  break;
		 case '3': SM1_output[0] = '3';  break;
		 case '4': SM1_output[0] = '4';  break;
		 case '5': SM1_output[0] = '5';  break;
		 case '6': SM1_output[0] = '6';  break;
		 case '7': SM1_output[0] = '7';  break;
		 case '8': SM1_output[0] = '8';  break;
		 case '9': SM1_output[0] = '9';  break;
		 case 'A': SM1_output[0] = 'A';  break;
		 case 'B': SM1_output[0] = 'B';  break;
		 case 'C': SM1_output[0] = 'C';  break;
		 case 'D': SM1_output[0] = 'D';  break;
		 case '*': SM1_output[0] = '*';  break;
		 case '0': SM1_output[0] = '0';  break;
		 case '#': SM1_output[0] = '#';  break;
		 default: SM1_output[0] = SM1_output[0];  break; // Should never occur. Middle LED off.
	 }
	 break;
	 
	default:
	break;
	}
	return state;
}

//Enumeration of states.
enum SM2_States { SM2_init, SM2_scroll };
/*
// If paused: Do NOT toggle LED connected to PB0
// If unpaused: toggle LED connected to PB0
int SMTick2(int state) {

	//State machine transitions
	switch (state) {
	
	case SM2_init:
	state = SM2_scroll;
	break;
	
	case SM2_scroll:
	state = SM2_scroll;
	break;

	default:	
	state = SM2_init;	
	break;
	}

	//State machine actions
	switch(state) {
	case SM2_init:
	i = 0;
	break;

	case SM2_scroll:
	if(i < 16){
		SM2_output[i] = all_string[i];
		i++;
	}
	else if(i < sizeof(all_string)){
		for(int j = 0; j < 15; j++){
			SM2_output[j] = SM2_output[j + 1];
		}
		SM2_output[15] = all_string[i];
		i++;
	}
	else{
		i = 0;
	}
	break;

	default:
	break;
	}

	return state;
}

//Enumeration of states.
enum SM3_States { SM3_wait, SM3_blink };

// If paused: Do NOT toggle LED connected to PB1
// If unpaused: toggle LED connected to PB1
int SMTick3(int state) {
	//State machine transitions
	switch (state) {
	case SM3_wait:	if (pause == 0) {	// If unpaused, go to blink state
state = SM3_blink;
}
break;

	case SM3_blink:	if (pause == 1) {	// If paused, go to wait state
state = SM3_wait;
}
break;

	default:		state = SM3_wait;
				break;
	}

	//State machine actions
	switch(state) {
	case SM3_wait:	break;

	case SM3_blink:	SM3_output = (SM3_output == 0x00) ? 0x02 : 0x00; //toggle LED
				break;

	default:		break;
	}

	return state;
}

*/
//Enumeration of states.
enum SM4_States { SM4_display };

// Combine blinking LED outputs from SM2 and SM3, and output on PORTB
int SMTick4(int state) {
	// Local Variables

	unsigned char output;
	

	//State machine transitions
	switch (state) {
	case SM4_display:	
	break;

	default:
	state = SM4_display;
	break;
	
	}

	//State machine actions
	switch(state) {
	case SM4_display:	
	output = SM1_output; // write shared outputs
	break;

	default:		break;
	}

	//PORTB = output;	// Write combined, shared output variables to PORTB
	//LCD_DisplayString(1,SM1_output);
	LCD_Cursor(1);
	LCD_WriteData(SM1_output[0]);
	//LCD_DisplayString(1, "eat my ass");
	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
// Set Data Direction Registers
// Buttons PORTA[0-7], set AVR PORTA to pull down logic
DDRA = 0xFF; PORTA = 0x00;
DDRB = 0xFF; PORTB = 0x00;
DDRC = 0xF0; PORTC = 0x0F;
DDRD = 0xFF; PORTD = 0x00;
// . . . etc

// Period for the tasks
unsigned long int SMTick1_calc = 100;
//unsigned long int SMTick2_calc = 250;
//unsigned long int SMTick3_calc = 250;
unsigned long int SMTick4_calc = 100;

//Calculating GCD
unsigned long int tmpGCD = 1;
tmpGCD = findGCD(SMTick1_calc, SMTick4_calc);
//tmpGCD = findGCD(tmpGCD, SMTick4_calc);
//tmpGCD = findGCD(tmpGCD, SMTick3_calc);

//Greatest common divisor for all tasks or smallest time unit for tasks.
unsigned long int GCD = tmpGCD;

//Recalculate GCD periods for scheduler
unsigned long int SMTick1_period = SMTick1_calc/GCD;
//unsigned long int SMTick2_period = SMTick2_calc/GCD;
//unsigned long int SMTick3_period = SMTick3_calc/GCD;
unsigned long int SMTick4_period = SMTick4_calc/GCD;

//Declare an array of tasks 
static task task1, task4 ;
task *tasks[] = { &task1, &task4 };
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

// Task 1
task1.state = -1;//Task initial state.
task1.period = SMTick1_period;//Task Period.
task1.elapsedTime = SMTick1_period;//Task current elapsed time.
task1.TickFct = &SMTick1;//Function pointer for the tick.
/*
// Task 2
task2.state = -1;//Task initial state.
task2.period = SMTick2_period;//Task Period.
task2.elapsedTime = SMTick2_period;//Task current elapsed time.
task2.TickFct = &SMTick2;//Function pointer for the tick.

// Task 3
task3.state = -1;//Task initial state.
task3.period = SMTick3_period;//Task Period.
task3.elapsedTime = SMTick3_period; // Task current elasped time.
task3.TickFct = &SMTick3; // Function pointer for the tick.
*/
// Task 4
task4.state = -1;//Task initial state.
task4.period = SMTick4_period;//Task Period.
task4.elapsedTime = SMTick4_period; // Task current elasped time.
task4.TickFct = &SMTick4; // Function pointer for the tick.

// Set the timer and turn it on
TimerSet(GCD);
TimerOn();

LCD_init();

unsigned short i; // Scheduler for-loop iterator
while(1) {
	// Scheduler code
	for ( i = 0; i < numTasks; i++ ) {
		// Task is ready to tick
		if ( tasks[i]->elapsedTime == tasks[i]->period ) {
			// Setting next state for task
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			// Reset the elapsed time for next tick.
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 1;
	}
	while(!TimerFlag);
	TimerFlag = 0;
}

// Error: Program should not exit!
return 0;
}



