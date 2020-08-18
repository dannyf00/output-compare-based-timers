#ifndef _TMROC3_H
#define _TMROC3_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
//end hardware configuration

//global defines
#define TMROC_ms				(F_CPU / 1000)
//global variables

//to include in isr
//  if (CCP3IF) ccp3_isr();

//ccpx isr
//flag (CCP3IF) is cleared in ccp2_isr
void ccp3_isr(void);
	
//set up the oc1 as a timer
void tmroc3_init(uint16_t pr);

//install user handler
void tmroc3_act(void (*isr_ptr)(void));

#endif
