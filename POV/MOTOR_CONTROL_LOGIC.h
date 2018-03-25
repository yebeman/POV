#ifndef MOTOR_CONTROL_LOGIC
#define MOTOR_CONTROL_LOGIC

/*****
	TITLE: MOTOR CONTROL
	TYPE: Interrupt /External/ & Timer
	SUBTYPE: 8bit - NO:2   -  CTC MODE
	PORT: PORT:D7
	FURTHER DESC: - Fast PWM - only allows u to change duty on NO:2, THUS -> CTC
				  - USED http://eleccelerator.com/avr-timer-calculator/
	YEBE
*/


#define TICKS 25;





#include "MOTOR_CONTROL_LOGIC.c"
#endif