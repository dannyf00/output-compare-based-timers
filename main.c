#include "config.h"						//configuration words
#include "gpio.h"                           //we use gpio functions
#include "delay.h"                          //we use software delays
#include "tmr1.h"							//we use timer1
#include "tmroc1.h"							//we use oc1 as a timer
#include "tmroc2.h"							//we use oc2 as a timer
#include "tmroc3.h"							//we use oc3 as a timer
#include "tmroc4.h"							//we use oc4 as a timer
#include "tmroc5.h"							//we use oc5 as a timer

//hardware configuration
#define LED_PORT		LATB
#define LED_DDR			TRISB
#define LED				(1<<0)
#define LED1			(1<<1)
#define LED2			(1<<2)
#define LED3			(1<<3)
#define LED4			(1<<4)
#define LED5			(1<<5)
#define LED1_DLY		1000ul
#define LED2_DLY		1250ul
#define LED3_DLY		1500ul
#define LED4_DLY		1750ul
#define LED5_DLY		2000ul
//end hardware configuration

//global defines

//global variables

//isr
void interrupt isr(void) {
	//ccp isr, fromo highest to lowest priority
	if (CCP1IF) ccp1_isr();
	if (CCP2IF) ccp2_isr();
	if (CCP3IF) ccp3_isr();
	if (CCP4IF) ccp4_isr();
	if (CCP5IF) ccp5_isr();
}		
	
//flip an led
void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}

void led1_flp(void) {IO_FLP(LED_PORT, LED1);}
void led2_flp(void) {IO_FLP(LED_PORT, LED2);}
void led3_flp(void) {IO_FLP(LED_PORT, LED3);}
void led4_flp(void) {IO_FLP(LED_PORT, LED4);}
void led5_flp(void) {IO_FLP(LED_PORT, LED5);}

int main(void) {
	
	mcu_init();							    //initialize the mcu
	tmr1_init(TMR1_PS1x);					//initialize timer1 as timebase for output compare
	//set up oc1
	tmroc1_init(LED1_DLY); tmroc1_act(led1_flp);	//install user handler
	tmroc2_init(LED2_DLY); tmroc2_act(led2_flp);	//install user handler
	tmroc3_init(LED3_DLY); tmroc3_act(led3_flp);	//install user handler
	tmroc4_init(LED4_DLY); tmroc4_act(led4_flp);	//install user handler
	tmroc5_init(LED5_DLY); tmroc5_act(led5_flp);	//install user handler
	//reset the led pins
	IO_CLR(LED_PORT, LED | LED1 | LED2 | LED3 | LED4 | LED5);
	IO_OUT(LED_DDR, LED | LED1 | LED2 | LED3 | LED4 | LED5);
	ei();									//enable global interrupt
	while (1) {
		IO_FLP(LED_PORT, LED);				//flip led
	}
}

