#ifndef _TMROC5_H
#define _TMROC5_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
//end hardware configuration

//global defines
#define TMROC_ms				(F_CPU / 1000)
//global variables

//to include in isr
//  if (CCP5IF) ccp5_isr();

//ccpx isr
//flag (CCP5IF) is cleared in ccp2_isr
void ccp5_isr(void);
	
//set up the oc1 as a timer
void tmroc5_init(uint16_t pr);

//install user handler
void tmroc5_act(void (*isr_ptr)(void));

#endif
