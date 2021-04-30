/*
 * task1-decimal-counter.c
 *
 * Created: 10-Apr-21 2:07:25 PM
 * Author : Refaey
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "libs/DIO.h"
#include "libs/Button.h"
#include "libs/Seven_Segment_BCD_ETA32.h"

#define BUTTON_PIN 0
#define SEG1_EN_PIN 3
#define SEG2_EN_PIN 2
#define SEG3_EN_PIN 5
#define SEG4_EN_PIN 6

int main(void)
{
	unsigned char counter = 0;
	unsigned char units = counter%10;
	unsigned char tens = counter/10;
	unsigned char btn_value = 0;
	
	// Initialize Button
	Button_Initialize('A', BUTTON_PIN);
	
	// Initialize Seven Segments
	SevenSegment_BCD_ETA32_SetUp('B');
	
	// Disable 4 Segments in the start
	SevenSegment_BCD_ETA32_Disable('A', SEG1_EN_PIN);
	SevenSegment_BCD_ETA32_Disable('A', SEG2_EN_PIN);
	SevenSegment_BCD_ETA32_Disable('B', SEG3_EN_PIN);
	SevenSegment_BCD_ETA32_Disable('B', SEG4_EN_PIN);
	
    while (1) 
    {
		btn_value = Button_Read('A', BUTTON_PIN);
		units = counter%10;
		tens = counter/10;
		
		// Enable Units Segment and write value
		SevenSegment_BCD_ETA32_Enable('A', SEG2_EN_PIN);
		SevenSegment_BCD_ETA32_Display('B', units);
		_delay_ms(30);
		SevenSegment_BCD_ETA32_Disable('A', SEG2_EN_PIN);

		// Enable Tens Segment and write value
		SevenSegment_BCD_ETA32_Enable('A', SEG1_EN_PIN);
		SevenSegment_BCD_ETA32_Display('B', tens);
		_delay_ms(30);
		SevenSegment_BCD_ETA32_Disable('A', SEG1_EN_PIN);
			
		
		// Increase Seven_Segment value with each press
		if (btn_value == 1)
		{
			counter++;
			_delay_ms(180);
		}
		
		// Reset the counter when reached 100
		if (counter > 99)
		{
			counter = 0;
		}
		
    }
}

