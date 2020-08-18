#ifndef _TMROC2_H
#define _TMROC2_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
//end hardware configuration

//global defines
#define TMROC_ms				(F_CPU / 1000)
//global variables

//to include in isr
//  if (CCP2IF) ccp2_isr();

//ccpx isr
//flag (CCP2IF) is cleared in ccp2_isr
void ccp2_isr(void);
	
//set up the oc1 as a timer
void tmroc2_init(uint16_t pr);

//install user handler
void tmroc2_act(void (*isr_ptr)(void));

#endif
