/*
 * ioc_test.c
 *
 * Created: 1/31/2019 12:07:24 PM
 * Author : ericj
 */ 

#include <avr/io.h>
#include "io.c"

int main(void)
{
    /* Replace with your application code */
   DDRC = 0xFF; PORTC = 0x00; // LCD data lines
   DDRD = 0xFF; PORTD = 0x00; // LCD control lines
   
   // Initializes the LCD display
   LCD_init();
   
   // Starting at position 1 on the LCD screen, writes Hello World
   LCD_DisplayString(1, "Hello World");
   
   while(1) {continue;}
}

