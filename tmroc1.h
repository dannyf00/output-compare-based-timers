#ifndef _TMROC1_H
#define _TMROC1_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
//end hardware configuration

//global defines
#define TMROC_ms				(F_CPU / 1000)
//global variables

//to include in isr
//  if (CCP1IF) ccp1_isr();

//ccpx isr
//flag (CCP1IF) is cleared in ccp1_isr
void ccp1_isr(void);
	
//set up the oc1 as a timer
void tmroc1_init(uint16_t pr);

//install user handler
void tmroc1_act(void (*isr_ptr)(void));

#endif
