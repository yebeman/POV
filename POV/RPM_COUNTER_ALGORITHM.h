#ifndef RPM_COUNTER_ALGORITHM
#define RPM_COUNTER_ALGORITHM

/*****
	TITLE: RPM COUNTER
	TYPE: Interrupt /External/ & Timer
	SUBTYPE: Int/NO:0, Trig:0->1/
	PORT: PORT:D2
	
	YEBE
*/

volatile int revolutionCount = 0;
volatile float RPM = 0;
volatile uint16_t msRevPeriod = 0;
volatile bool interrOccurred = false;
int tolleranceMeter = 0;



#include "RPM_COUNTER_ALGORITHM.c"
#endif