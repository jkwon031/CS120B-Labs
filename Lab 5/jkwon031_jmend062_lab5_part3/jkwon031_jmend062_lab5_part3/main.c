/*	Partner(s) Name & E-mail: Jason Mendoza & jmend062@ucr.edu
 *	Lab Section: 021
 *	Assignment: Lab # 5 Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
/*
 * jkwon031_jmend062_lab5_part3.c
 *
 * Created: 1/27/2019 11:18:18 PM
 * Author : ericj
 */ 

#include <avr/io.h>
    enum States {Init, stayI, stayd, zeroI, zeroD, increment, deincrement, holdI, holdD} state;
    unsigned char total = 0x00;
    unsigned char A0;

    void Tick(){
	    A0 = (~PINA) & 0x01;
	    switch(state){
		    case Init:
				state = stayI;
				break;
		    case stayI:
				if(A0 && total != 0x7F){
					state = increment;
				}else if (!A0 && total != 0x7F){
					state = stayI;
				}else if (A0 && total == 0x7F){
					state = zeroI;
				}else{
					state = zeroI;
				}
				break;
		    case increment:
				if (A0){
					state = holdI;
				}else{
					state = stayI;
				}
				break;
		    case holdI:
				if (A0){
					state = holdI;
				}else{
					state = stayI;
				}
				break;
		    case holdD:
				if(A0){
					state = holdD;
				}else{
				   state = stayd;
				}
				break;
		    case zeroI:
				if(A0){
					state = deincrement;
				}else{
					state = zeroI;
				}
				break;
		    case zeroD:
				if(!A0){
					state = stayI;
				}else{
					state = zeroD;
				}
				break;
		    case stayd:
				if(A0 && total != 0x3F){
					state = deincrement;
				}else if (!A0 && total != 0x3F){
					state = stayd;
				}else if(A0 && (total & 0x01) == 1 ){
					state = zeroD;
				}
				break;
		    case deincrement:
				if(A0){
					state = holdD;
				}else{
					state = stayd;
				}
				break;
		    default:
				state = Init;
				break;
	    }
	    switch(state){
		    case Init:
				total = 0x00;
				break;
		    case zeroI:
				total = 0x00;
				break;
		    case zeroD:
				total = 0x00;
				break;
		    case holdD:
				break;
		    case holdI:
				break;
		    case stayd:
				break;
		    case stayI:
				break;
		    case increment:
				total  = (total << 1) + 0x01;
				break;
		    case deincrement:
				total  = (total >> 1) + 0x20;
				break;
	    }
	    PORTB = total;
    }
    int main(void)
    {
	    PORTA = 0xFF; DDRA = 0x00;
	    PORTB = 0x00; DDRB = 0xFF;
	    
	    
	    total = 0x00;
	    state = Init;
	    while (1)
	    {
		    Tick();
	    }
	}

