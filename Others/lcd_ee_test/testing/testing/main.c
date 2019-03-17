/*
 * testing.c
 *
 * Created: 3/13/2019 10:25:36 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "io.c"


int main(void)
{
	 DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	 DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	char buffer[7];
	LCD_init();
	itoa(10, buffer, 10);
	LCD_ClearScreen();
	LCD_DisplayString(1, buffer);
    /* Replace with your application code */
    while (1) 
    {

    }
}

