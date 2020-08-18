#ifndef _TMROC4_H
#define _TMROC4_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
//end hardware configuration

//global defines
#define TMROC_ms				(F_CPU / 1000)
//global variables

//to include in isr
//  if (CCP4IF) ccp4_isr();

//ccpx isr
//flag (CCP4IF) is cleared in ccp2_isr
void ccp4_isr(void);
	
//set up the oc1 as a timer
void tmroc4_init(uint16_t pr);

//install user handler
void tmroc4_act(void (*isr_ptr)(void));

#endif
