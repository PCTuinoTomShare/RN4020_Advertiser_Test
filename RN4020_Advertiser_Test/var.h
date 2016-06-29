/*
 * var.h
 *
 * Created: 2016/6/26 下午 11:54:25
 *  Author: tom hsieh
 */ 

#include <avr/io.h>

#ifndef VAR_H_
#define VAR_H_

// RN4020 command, stop broadcast.
uint8_t cmd_stop_broadcast[2];
// RN4020 command, start broadcast.
// interval 500ms for 2sencond.
uint8_t cmd_start_broadcast[12];

// Temporary #1.
uint8_t temp1;
// Temporary #2.
uint8_t temp2;

// UART #0 data received
uint8_t uart0_rec_data[33];
// UART #0 data count.
uint8_t uart0_rec_cnt;
// UART #0 received timeout.
uint8_t uart0_rec_to;
// UART #0 transmit data. 
uint8_t uart0_trn_data[16];
// UART #0 output data pointer.
uint8_t *puart0_trn_data;

// UART #0 data transmitted count.
uint8_t uart0_trn_cnt;

// TWI #0 task count.
uint8_t twi0_task_cnt;
// TWI #0 task status flag.
uint8_t twi0_task_status;
// TWI #0 data.
uint8_t twi0_data[32];
// TWI #0 data index.
uint8_t twi0_data_index;
// TWI #0 data count.
uint8_t twi0_data_cnt;
// TWI #0 SLA.
uint8_t twi0_addr;
// TWI #0 control word.
uint8_t twi0_word;
// Device task count.
uint8_t dev_task_cnt;
// HIH6130 measurement delay.
uint8_t meas_delay;
// HIH6130 measurement value character.
uint8_t hih6130_value[13];


#endif /* VAR_H_ */