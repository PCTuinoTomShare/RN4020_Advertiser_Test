/*
 * File:   HIH6130.c
 * Author: tom hsieh
 *
 * Created on 2014?11?1?, ?? 10:05
 */


#include "TWI_Task.h"
#include "HIH6130.h"
#include "convert.h"
#include "var.h"

// Measurement request.
void HIHI6130_Measure_Request( void )
{
	// SLA.
    twi0_addr = HIH6130_WR;        
    // Trigger on write task.
	TWI0_On_Write();
	// Set task count.
	twi0_task_cnt = 19;
}

// Read humidity and temperature data.
void HIH6130_I2C_On_HT( void )
{	
	// SLA.
    twi0_addr = HIH6130_RD;        	
	// 4 byte to read.
	twi0_data_cnt = 4;
	// Trigger on read task.
	TWI0_On_Read();	
}

// Get humidity and temperature.
void HIH6130_Get_HT( void )
{
	// Humidity high byte.
	temp1 = twi0_data[0];
	temp1 >>= 4;
	ToChracter();
	hih6130_value[2] = temp1;		
	temp1 = twi0_data[0];
	temp1 &= 0x0f;
	ToChracter();	
	hih6130_value[3] = temp1;
	// Humidity low byte.
	temp1 = twi0_data[1];
	temp1 >>= 4;
	ToChracter();
	hih6130_value[4] = temp1;	
	temp1 = twi0_data[1];
	temp1 &= 0x0f;
	ToChracter();	
	hih6130_value[5] = temp1;
	// Temperature high byte.	
	temp1 = twi0_data[2];
	temp1 >>= 4;
	ToChracter();
	hih6130_value[6] = temp1;	
	temp1 = twi0_data[2];
	temp1 &= 0x0f;
	ToChracter();	
	hih6130_value[7] = temp1;
	// Temperature low byte.
	temp1 = twi0_data[3];
	temp1 >>= 4;
	ToChracter();
	hih6130_value[8] = temp1;
	temp1 = twi0_data[3];
	temp1 &= 0x0f;
	ToChracter();	
	hih6130_value[9] = temp1;
	
	// Prepare UART transmitting data.
	puart0_trn_data = hih6130_value;
	uart0_trn_cnt = 11;	
}
