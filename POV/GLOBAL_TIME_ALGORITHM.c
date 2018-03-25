/*****
	
	YEBE
	
******/

///////////////////////////////////////////////////////////////////////////////////////////////
// GLOBAL TIME - 
// Currently Using: Timer/Counter /8bit - NO:0/
//////////////

void initTime(void){
	// get 1000Hz - 1ms
	// 64 div - 250 ticks
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS00) | (1 << CS01);
	TIMSK0 |= (1 << OCIE0A);
	TCNT0 = 0;
	OCR0A = 250;

}

ISR (TIMER0_COMPA_vect)
{

	//currTime_mS ++;
	cli();
	currTime_mS >= 60000 ? currTime_mS = 0 : currTime_mS ++ ;
	
	// for timing purpose -> can be reseted
	currTime_mS_Timing >= 60000 ? currTime_mS_Timing = 0 : currTime_mS_Timing ++ ;
	
	// for timing RPM purpose -> can be reseted
	currTime_mS_TimingRPM >= 60000 ? currTime_mS_TimingRPM = 0 : currTime_mS_TimingRPM ++ ;

	if (!(currTime_mS % 1000)){
		currTime_S ++;
		currTime_S_Timing++;
		currTime_mS_TimingRPM++;
	}
	
	if (currTime_S >= 60){
		currTime_M ++;
		currTime_S = 0;
		
		// timing
		currTime_M_Timing ++;
		currTime_S_Timing = 0;
	}
	
	if (currTime_M >= 60){
		currTime_H ++;
		currTime_M = 0;
		currTime_S = 0;
		
		// timing
	}
	
	sei();
}


// reset time
void resetTime(void){
	currTime_mS = 0;
	currTime_S = 0;
	currTime_M = 0;
	currTime_H = 0;
}

// reset time
void resetRPMTime(void){
  currTime_mS_TimingRPM = 0;
}

// reset timer
void resetTimer(void){
	currTime_mS_Timing = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////