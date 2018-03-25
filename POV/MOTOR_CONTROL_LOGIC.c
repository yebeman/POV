/*****
	
	YEBE
	
******/
///////////////////////////////////////////////////////////////////////////////////////////////
// MOTOR CONTROL -
// Timer/Counter /8bit - NO:2/ - Port:D7 
//////////////


void initMotor(){
	
	// disable interrupts
	cli();
	
	
	// port setup
	DDRD |= (1<<PORTD7);
	
	//set registers
	// get 38KHz
	// set CTC mode /hardware enabled - toggle/ - 8 div
	TCCR2A =	(1 << WGM21) | (1 << COM2A0);
	TCCR2B =	(1 << CS21);
	
	// initialize compare value - 52 ticks /52.63/  - 38461Hz
	OCR2A = TICKS;
	
	// reenable interrupts
	sei();
}

// control 
void motorFunction(bool onOff){
	
	// turn on
	if(onOff)
	{
		// set  clock source
		TCCR2B =	(1 << CS21);
	}
	else
	{
		// turn it off
		// set no clock source
		TCCR2B =	(0 << CS21);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////