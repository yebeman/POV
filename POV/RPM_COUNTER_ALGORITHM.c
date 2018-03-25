/*****
	
	YEBE
	
******/
///////////////////////////////////////////////////////////////////////////////////////////////
// RPM COUNTER -
// Interrupt /External/ & Timer - Int/NO:0, Trig:0->1/ - PORT:D2
//////////////

void initRPMCounter(void) {
	cli();
	
	// port setup
	DDRD = (1 << PORTD2);
	EICRA = (1 <<ISC01);
	EIMSK = (1 << INT0);
	sei();
}

ISR(INT0_vect){
	
	cli();
	msRevPeriod = currTime_mS_TimingRPM;
	RPM = 60000/currTime_mS_TimingRPM;
	
	resetRPMTime();
	interrOccurred = true;
	sei();
}

///////////////////////////////////////////////////////////////////////////////////////////////