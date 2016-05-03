/*
 * common.h
 *
 *  Created on: 10.04.2016 ã.
 *      Author: ilian
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_


//volatile uint8_t   count=0;
volatile  uint16_t  temp[2];

/********************************************************************
*   Timers
********************************************************************/
volatile uint16_t hwclock;
volatile uint16_t int_clock;
volatile uint16_t pulse_counter;
volatile uint16_t gear_num;
volatile uint16_t temp_freq_start_IPG;
volatile uint16_t temp_freq_end_IPG;
volatile int measure_flag_IPG;

volatile uint16_t gear1[2];
volatile uint16_t gear2[2];
volatile uint16_t gear3[2];
volatile uint16_t gear4[2];
volatile uint16_t gear5[2];
volatile uint16_t gear6[2];

#endif /* COMMON_COMMON_H_ */
