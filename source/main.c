/*
 * main.c
 *
 *  Created on: 10.04.2016 ã.
 *      Author: ilian
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "main.h"
#include "init/USART_Init.h"
#include "IO/io_setup.h"
#include "common/common.h"
#include "init/set_interrupt.h"
#include "library/7_SEG_Led.h"
#include "library/learn.h"
#include "init/restore.h"
#include "library/measure.h"

#define HWCLOCK_RESETCNT    280
#define TICKSPERSEC        (F_CPU/1000/HWCLOCK_RESETCNT)

//DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//DEBUG

#ifdef DEBUG
FILE uart_str = FDEV_SETUP_STREAM(uart_putch, uart_getch, _FDEV_SETUP_RW);
#endif

/********************************************************************
*   Timer 2 interrupt routine, 1ms ticks
*
********************************************************************/
ISR(TIMER2_OVF_vect){

	/*
	 * Set timer counter initial value
	 */
    TCNT2 = 0xFF - HWCLOCK_RESETCNT + 1;

	/*
	 * 16bit incremental counter, every 1ms
	 */
    if ( ++hwclock > TICKSPERSEC){
        hwclock = 0;
        int_clock++;
    }
}

ISR (INT0_vect)
{
    /* interrupt code here */
	   if(pulse_counter < 50 ){                                                     // _count increment every time, when VSS sensor make pulse cycle
		   pulse_counter++;                                                         // when VSS make 50 cycles, _count start from beginning.
	   }else{                                                                       // _count is used for counting how many IPG pulses have, for 50
		   pulse_counter = 0;                                                       // VSS cycles.
	   }

}
ISR (INT1_vect)
{
	if(!measure_flag_IPG){
		temp_freq_start_IPG = int_clock;
		measure_flag_IPG = 1;
	}else{
		temp_freq_end_IPG = int_clock;
		measure_flag_IPG = 0;
	}
}

int main(void){

//********************** Declaration of variables ******************************
//	signed int measure;
//	signed int a = -1;
	int i=0;
	uint16_t staus_poll  =0;
	uint16_t temp_result =0;

//********************** Initialization of variables ******************************
	hwclock = 0;
	int_clock = 0;
	pulse_counter = 0;
	measure_flag_IPG = 0;

#ifdef DEBUG
/*
 *  Initialize device
 */
USART_Init();
#endif
/*
 * Initializing I/O Ports
 */
io_init();

/*
 * Initializing interrupt
 */
set_timer2_interrupt();
set_external_interrupt();

/*
 *  Global Interrupt Enable flag set
 */
sei();
//cli();

/*
 *Set VSS interrupt
 */
enable_VSS_interrupt();

/*
 *Set IPG interrupt
 */
disable_IPG_interrupt();


#ifdef DEBUG
/*
 * Set usart stream
 */
stdout = stdin = &uart_str;
printf("START\r\n");
#endif

//Learn device routine
if(LEARN_SW)learn_device();

//Restore settings from EEPROM
restore();

/*
 * Main Loop
 */
	while(1){

		/*
		 * measure poll every 10 ms
		 */
		if ((int_clock - staus_poll) >= 10) {

			temp_result = read_puls_20();
#ifdef DEBUG
			printf("res > %d\r\n", temp_result);
#endif
			for (i=1; i <= gear_num; i++){

				switch (i){
					case 1 :
						if((temp_result >= gear1[0]) && (temp_result <= gear1[1])) led_char(1);
					break;
					case 2 :
						if((temp_result >= gear2[0]) && (temp_result <= gear2[1])) led_char(2);
					break;
					case 3 :
						if((temp_result >= gear3[0]) && (temp_result <= gear3[1])) led_char(3);
					break;
					case 4 :
						if((temp_result >= gear4[0]) && (temp_result <= gear4[1])) led_char(4);
					break;
					case 5 :
						if((temp_result >= gear5[0]) && (temp_result <= gear5[1])) led_char(5);
					break;
					case 6 :
						if((temp_result >= gear6[0]) && (temp_result <= gear6[1])) led_char(6);
					break;
					default :
					break;

				};
			}
			staus_poll = int_clock;
		}

		/*
		 *  Check for neutral position
		 */
		if (NEUTRAL_SW){
			led_char(0);
			while(NEUTRAL_SW);
		}
	}
return 0;
}
