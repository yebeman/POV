#ifndef GLOBAL_TIME_ALGORITHM
#define GLOBAL_TIME_ALGORITHM

volatile uint16_t currTime_mS = 0;
volatile uint16_t currTime_S = 0;
volatile uint16_t currTime_M = 0;
volatile uint16_t currTime_H = 0;

volatile uint16_t currTime_mS_Timing = 0;
volatile uint16_t currTime_S_Timing = 0;
volatile uint16_t currTime_M_Timing = 0;
volatile uint16_t currTime_H_Timing = 0;

volatile uint16_t currTime_mS_TimingRPM = 0;


#include "GLOBAL_TIME_ALGORITHM.c"
#endif