/*****
	
	YEBE
	
******/
///////////////////////////////////////////////////////////////////////////////////////////////
// LED SETUP & CONTROL -
// 
//////////////

//adjust GSDL from btm -> top on all
void adjustGSDL(void){
	int counter = 0;
	
	for (int i=0; i < NUMBER_OF_BOARD; i++){
		for (int j=0; j < NUMBER_OF_LED_PER_BOARD; j++){
			for (int k=0; k < NUMBER_OF_SUBLED_PER_LED/2; k++){
			
				
					adjustedGSDL[i][j][k] =	startBottomNowWeHere[counter] + i*96; 
					counter += 2;
					
						char numberCharBuff[20];
						itoa(adjustedGSDL[i][j][k],numberCharBuff,10);
						USART_Print(numberCharBuff);
						
						USART_Transmit(':');
						
						char numberCharBuffa[20];
						itoa(j,numberCharBuffa,10);
						USART_Print(numberCharBuffa);
						
						_delay_ms(10);			
						USART_Print("BB\r\n");
						
			
			}
		}
		
		// reset
		counter = 0;
	}
}

void printLED(void){
	for (int i=0; i < NUMBER_OF_LED; i++){
			spi_tranceiver(GSDL[i]);
	}
}


// clear GSDL & adjustGSDL
void clearFrame(){

		for (int i=0; i < NUMBER_OF_LED; i++){
					GSDL[i] = 0x00;
		}
}

// set each sub led inside pixel
void setSubLED(int board, int LED, int subLED, uint16_t data){
	
	//42 -> 0,0,0    43 -> 0,0,0  -> 16bits - data
	//44 -> 0,0,1	 45 -> 0,0,1  -> 16bits - data
	// R,G,B
	
	byte leftByte = data;
	byte rightByte =  ((data & 0xFF00) >> 8 );
		
		if(board * LED * subLED < NUMBER_OF_LED)
		{
			
			long gsdlAddress = adjustedGSDL[board][LED][subLED];
			
			if(board > 0){
				GSDL[gsdlAddress] =  leftByte;
				GSDL[gsdlAddress+1] =  rightByte;
			}
			else {
				GSDL[gsdlAddress] =  leftByte;
				GSDL[gsdlAddress-1] =  rightByte;
			}
			
		}
	
}

// set RGB 
void setPixel(int board, int LED, uint16_t RED, uint16_t GREEN, uint16_t BLUE){

	setSubLED(board,LED, 0, BLUE);
	setSubLED(board,LED, 1, GREEN);
	setSubLED(board,LED, 2, RED);
	
}


void updateScreen(){
	printLED();
	latch_tlc();
	}
	
// modifies bits on GSDL with a given character using collectionOfCharacters[][6] implementation
bool writeChar(int board, int beginFromY, unsigned char character, uint16_t switchTime, uint16_t RED, uint16_t GREEN, uint16_t BLUE) {
		
		resetTimer(); 
		uint16_t timedivStart=currTime_mS_Timing;
		int charCounter = 0;
		int goThough = 0;  // max is 6 to current standard
		bool found = false;
		
		// search and find char
		while(charCollectionSize > charCounter){
			
			if(collectionOfCharactersGuide[charCounter] == character)
				{
					found = true;
					break;
				}
			charCounter++;
		}
		

			
		// go through with switchTime interval if found
		while(found){
			
			if((currTime_mS_Timing - timedivStart) >= switchTime/6){
				
				// ready for printing 
				flushTLC();
				spi_tranceiver(gsMode);
				clearFrame();		
					
					for (int i=0; i<8; i++)
					{
						if(bitRead(collectionOfCharacters[charCounter][goThough], 8-i))
							{			
								setPixel(board, beginFromY + i ,RED,GREEN,BLUE);
							}
					}
			
		
		
				// break if we finish printing
				if(goThough < 6){
					goThough++;
					}
				else
					break;
				
				timedivStart = currTime_mS_Timing;
				}
				
		// update screen with new information
		updateScreen();		
						
		};
		
		return found;
}

/*
42BB
44BB
46BB
18BB
20BB
22BB
36BB
38BB
40BB12BB
14BB
16BB
6BB
8BB
10BB
30BB
32BB
34BB
0BB
4BB
24BB
26BB
28BB
48BB
50BB
52BB
72BB
74BB
76BBB
56BB
58BB
78BB
80BB
82BB
84BB
86BB
88BB
60BB62BB
64BB
90BB
92BB
94BB
66BB
68BB
70BB
138BBB
142BB
114BB
116BB
118BB
132BB
134BB
136BB
108BB0BB
112BB
102BB
104BB
106BB
126BB
128BB
130BB
96BBB
100BB
120BB
122BB
124BB
144BB
146BB
148BB
170BB
172BB
150BB
152BB
154BB
174BB
176BB
178BB
182BB
184BB
156BB
158BB
160BB
186BB
188BB
162BB
164BB
166BB
234BB
236BB
238BB
210BB
212BB
214BB228BB
230BB
232BB
204BB
206BB
208BB
198BB
200BB02BB
222BB
224BB
226BB
192BB
194BB
196BB
216BB
218BB20BB
240BB
242BB
244BB
8BB
10BB
12BB
246BB
250BB
14BB
16BB
18BB
20BB
22BB
24BB
252BB
254BBBB
26BB
28BB
30BB
2BB
4BB
6BB



42BB
44BB
46BB
18BB
20BB
22BB
36BB
38BB
12BB
14BB
16BB
6BB
8BB
10BB
30BB
32BB
34BB
0BBB
4BB
24BB
26BB
28BB
48BB
50BB
52BB
72BB
74BB
54BB
56BB
58BB
78BB
80BB
82BB
84BB
86BB
88BB
60BB62BB
64BB
90BB
92BB
94BB
66BB
68BB
70BB
138BB0BB
142BB
114BB
116BB
118BB
132BB
134BB
136BB
108BB110BB
112BB
102BB
104BB
106BB
126BB
128BB
130BB
98BB
100BB
120BB
122BB
124BB
144BB
146BB
148BB
170BB
172BB
150BB
152BB
154BB
174BB
176BB
178BBBB
182BB
184BB
156BB
158BB
160BB
186BB
188BB
190BB162BB
164BB
166BB
234BB
236BB
238BB
210BB
212BB14BB
228BB
230BB
232BB
204BB
206BB
208BB
198BB
202BB
222BB
224BB
226BB
192BB
194BB
196BB
216BBBB
220BB
240BB
242BB
244BB
264BB
266BB
268BB
246BB48BB
250BB
270BB
272BB
274BB
276BB
278BB
280BB
254BB
256BB
282BB
284BB
286BB
258BB
260BB
262BB



42BB
44BB
46BB
18BB
20BB
22BB
36BB
38BB0BB
12BB
14BB
16BB
6BB
8BB
10BB
30BB
32BB
34BB
2BB
4BB
24BB
26BB
28BB
48BB
50BB
52BB
72BB
74BBBB
54BB
56BB
58BB
78BB
80BB
82BB
84BB
86BB
88BBB
62BB
64BB
90BB
92BB
94BB
66BB
68BB
70BB
138BBBB
142BB
114BB
116BB
118BB
132BB
134BB
136BBB
110BB
112BB
102BB
104BB
106BB
126BB
128BB
130BBBB
98BB
100BB
120BB
122BB
124BB
144BB
146BB
148BB8BB
170BB
172BB
150BB
152BB
154BB
174BB
176BB
180BB
182BB
184BB
156BB
158BB
160BB
186BB
188BBB
162BB
164BB
166BB
*/
///////////////////////////////////////////////////////////////////////////////////////////////									