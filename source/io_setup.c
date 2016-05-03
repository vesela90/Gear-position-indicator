/*
 * io_setup.c
 *
 *  Created on: 10.04.2016 ã.
 *      Author: ilian
 */

#include <avr/io.h>

#include "io_setup.h"

void io_init(void){

	DDRB   |=  (1 << PB0) |			    // LED Display port
			   (1 << PB1) |
			   (1 << PB2) |
			   (1 << PB3) |
			   (1 << PB4) |
			   (1 << PB5) |
			   (1 << PB6) ;

	LED_PORT = 0xFF;				    // All segments off

    DDRD   &= ~(1 << VSS_PIN)  |        // PD2 (INT0 pin) VSS pin as input
    	 	   (1 << IPG_PIN)  |		// Set IPG as input
			   (1 << LEARN_PIN)|		// Set LEARN_PIN as input
			   (1 << NEUTRAL_PIN); 	    // Set NEUTRAL_PIN as input

    PORTD  |=  (1 << VSS_PIN)  |        // turn On the Pull-ups
    		   (1 << IPG_PIN)  |
			   (1 << LEARN_PIN)|
			   (1 << NEUTRAL_PIN);


	DDRC   |=  (1 << PC0) |				// Output signals for debug
			   (1 << PC1);

	PORTC  &= ~(1 << PC0) |
			   (1 << PC1);

}
