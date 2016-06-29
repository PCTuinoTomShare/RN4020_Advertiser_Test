/*
 * convert.c
 *
 * Created: 2016/6/27 下午 02:51:50
 *  Author: tom hsieh
 */ 

#include <avr/io.h>
#include "convert.h"
#include "var.h"

// Convert value to character.
void ToChracter( void )
{
	// 0 ~ 9.
	if( temp1 < 10 ){
		temp1 += 0x30;
		return;
	}
	// A ~ F.
	temp1 -= 10;
	temp1 += 0x41;	
}