/*
 * Device_Task.c
 *
 * Created: 2016/6/27 上午 10:23:49
 *  Author: tom hsieh
 */ 

#include <avr/io.h>
#include "Device_Task.h"
#include "HIH6130.h"
#include "var.h"

// device task.
void Device_Task( void ){
	
	// TWI task busy check.
	temp1 = twi0_task_status;
	temp1 &= 0x01;
	if( temp1 ){
		// Still busy.
		return;
	}
	
	// UART data transmit busy check.
	if( uart0_trn_cnt ){
		// Still busy.
		return;
	}
	
	// check delay counter.
	if( meas_delay ){
		return;
	}
		
	switch( dev_task_cnt ){
				
		case 0:
			// Start HIH6130 measurement.	
			HIHI6130_Measure_Request();
			// Next task.
			++dev_task_cnt;
			// Reset measurement delay count.
			// 100ms.
			meas_delay = 10;
			break;
					
		case 1:
			// Read measurement data.
			HIH6130_I2C_On_HT();
			// Next task.
			++dev_task_cnt;			
			break;
		
		case 2:
			// Convert measurement value.
			// Update broadcast data.
			HIH6130_Get_HT();
			// Next task.
			++dev_task_cnt;
			// Reset measurement delay count.
			// 50ms.
			meas_delay = 5;						
			break;
			
		case 3:
			// Start broadcast.
			puart0_trn_data = cmd_start_broadcast;
			uart0_trn_cnt = 13;
			// Next task.
			++dev_task_cnt;
			// Reset measurement delay count.
			// 1200ms.
			meas_delay = 120;					
			break;
			
		case 4:
			// Stop broadcast.
			puart0_trn_data = cmd_stop_broadcast;
			uart0_trn_cnt = 2;
			// Next task.
			dev_task_cnt = 0;		
			break;	
	}
}
