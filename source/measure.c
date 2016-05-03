/*
 * measure.c
 *
 *  Created on: 15.04.2016 ã.
 *      Author: ilian
 */
#include <avr/io.h>
#include <avr/interrupt.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../IO/io_setup.h"
#include "../common/common.h"
#include "../init/set_interrupt.h"

int tachometer_time(void){
	int time = 0;
	return time;
}

uint16_t read_puls_20(void){											// Read IPG pulses for 10 VSS pulses

	uint16_t ipg_pulses = 0;
	pulse_counter = 0;

	do{
		while(IPG);														// Count every falling edge
		while(!IPG);

		ipg_pulses++;
		if (ipg_pulses > 1000) break;									// Error condition

	}while(pulse_counter < 20);

 return ipg_pulses;
}
