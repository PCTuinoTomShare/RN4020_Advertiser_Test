/*
 * Main.c
 *
 * Created: 2016/6/25 下午 06:40:35
 * Author : tom hsieh
 */ 

#include <avr/io.h>
#include <avr/fuse.h>
#include <avr/interrupt.h>
#include "Timer0_Task.h"
#include "UART_Task.h"
#include "TWI_Task.h"
#include "Device_Task.h"
#include "var.h"

FUSES = {
// 8MHz internal RC oscillator.
// Slow rising power.	
.low = (FUSE_SUT_CKSEL0 & FUSE_SUT_CKSEL2 & FUSE_SUT_CKSEL3 & FUSE_SUT_CKSEL4 ),
// Boot from 0x0000.
// SPI programming enable.
// debugWIRE enable.
.high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN & FUSE_DWEN ),
// No boot loader lock bit.
.extended = EFUSE_DEFAULT,
};

int main(void)
{
	// System clock prescaler 1.
	CLKPR = 0x80;  // Enable.
	CLKPR = 0x00;  // Write value.
	
	// Timer #0 initialize.
	Timer0_Init();
	// UART #0 initialize.
	UART0_Init();
	// TWI #0 initialize.
	TWI0_Init();
		
	// Variable reset.	
	// RN4020 command, stop broadcast.
	cmd_stop_broadcast[0] = 'X';
	cmd_stop_broadcast[1] = '\r';
	// RN4020 command, start broadcast.
	// interval 500ms for 2sencond.
	cmd_start_broadcast[0] = 'A';
	cmd_start_broadcast[1] = ',';	
	cmd_start_broadcast[2] = '0';
	cmd_start_broadcast[3] = '1';
	cmd_start_broadcast[4] = 'F';
	cmd_start_broadcast[5] = '4';
	cmd_start_broadcast[6] = ',';
	cmd_start_broadcast[7] = '0';
	cmd_start_broadcast[8] = '7';
	cmd_start_broadcast[9] = 'D';
	cmd_start_broadcast[10] = '0';
	cmd_start_broadcast[11] = '\r';			
	// RN4020 command, broadcast data update.
	hih6130_value[0] = 'N';
	hih6130_value[1] = ',';
	// CR character.	
	hih6130_value[10] = '\r';
	// Reset task counter.
	dev_task_cnt = 0;
	// Stop broad cast.
	puart0_trn_data = cmd_stop_broadcast;
	uart0_trn_cnt = 2;
			
	// Enable global interrupt.
	sei();

	// Power on delay.
	meas_delay = 50;
	while( meas_delay ){
		// Timer #0 task.
		Timer0_Task();
	}
	
    /* Replace with your application code */
    while (1) 
    {
		// Timer #0 task.
		Timer0_Task();
		// UART #0 transmit task.
		UART0_Trn_Task();
		// TWI #0 task.
		TWI0_Task();
		// TWI #0 device task.
		Device_Task();		
    }
}

