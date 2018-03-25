#ifndef CONFIGURATION_INDEX
#define CONFIGURATION_INDEX


#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


/////// debugging purposes

#define WIFI_ACTIVE 1
#define MOTOR_ACTIVE 0
#define RPM_ACTIVE 0


#endif