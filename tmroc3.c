#include "tmroc3.h"

//hardware configuration
//end hardware configuration

//global defines
#define CCPxCON			CCP3CON				//compare control register
#define CCPRxH			CCPR3H				//compare match register, msb
#define CCPRxL			CCPR3L				//compare match register, lsb
#define CCPxIF			CCP3IF
#define CCPxIE			CCP3IE
#define CCPRx			(*(uint16_t*)(&CCPRxL))
		
//empty handler
static void empty_handler(void) {
	//do nothing
}
//global variables
static uint16_t ocx_pr=0xffff;				//ocx period
static uint16_t ocx_ccpr;					//next match point
static void (* _isr_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//isr
void ccp3_isr(void) {
	CCPxIF = 0;								//clear the flag
	//set the match point
	//CCPRxH = ocx_ccpr >> 8; CCPRxL = ocx_ccpr;
	CCPRx  = ocx_ccpr;						//alternatively
	ocx_ccpr += ocx_pr;						//update the next match point
	_isr_ptr();								//execute user handler
}
		
//set up the oc3 as a timer
void tmroc3_init(uint16_t pr) {
	_isr_ptr = empty_handler;				//just in case
	ocx_pr = pr - 1;						//period
	CCPxCON = 0;							//reset compare module -> stop compare

	//set up the match registers
	ocx_ccpr = TMR1 + ocx_pr;
	//set the match point
	CCPRxH = ocx_ccpr >> 8; CCPRxL = ocx_ccpr;
	ocx_ccpr+= ocx_pr;						//advance to the next match point
		
	CCPxCON = 0b1010;						//generate software compare event only
	//compare on
}

//install user handler
void tmroc3_act(void (*isr_ptr)(void)) {
	_isr_ptr = isr_ptr;						//install user handler
	CCPxIF = 0;								//clear the flag
	CCPxIE = 1;								//1->enable the interrupt
	PEIE = 1;								//1->enable peripheral interrupt
}
