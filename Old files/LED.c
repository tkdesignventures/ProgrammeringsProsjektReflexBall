#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "charset.h"
#include "LED.h"
char buffer[5][6];


char lastString[];

int unitnr = 0;
int kolonnenr = 0;

int counter = 0;
int shift = 0;
int numberShifts = 0;

char done = 0;
int value = 0;
char mode = 1;

char string[] = "                                 ";

#pragma interrupt
void timer1int(){
	LEDUpdate();
}


void LEDInit(){
	PEDD = 0x00;
	PGDD = 0x00;	
	DI();
	T1CTL = 0x01; // Prescale value er 1, ingen division
	T1H = 0x00;
	T1L = 0x01;
	T1RH = 0x24; // Reload værdi er 9216  = 2400
	T1RL = 0x00;
	SET_VECTOR(TIMER1, timer1int);
	IRQ0ENL |= 0x40; //Sætter priority lav
	T1CTL |= 0x80; //Starter timeren
	EI();
	done = 0;
	counter = 0;
	numberShifts = 0;
	shift = 0;
	unitnr = 0;
	kolonnenr = 0;
	//string[] = "";
}

void setLedMode(char modeIn){
	mode = modeIn;
}

void LEDUpdate(){
	switch (mode){
		case 1: LedUpdatePrint(); break;
		case 2: LEDUpdateOnce(); break;
		//case 3: LEDUpdateContinuous; break;
	}
}

void LEDColumn(char value){         //"value" kunne også vært definert i toppen av filen.
	
	PGOUT = value;
	PEOUT = 0x1F;

	//Clock wave
	PEOUT |= 0x80;
	PEOUT &= 0x7F;
}

void LEDSetString(char *string1){
	int i,j;
	for(i = 0; string1[i] != '\0'; i++){
		string[i] = string1[i];
		
	}
	string[i] = '\0';
	done = 0;
	counter = 0;
	numberShifts = 0;
	shift = 0;
	kolonnenr = 0;
	unitnr = 0;
	
}

//Trenger kun at kaldes inden LEDUpdatePrint.
void LEDLoadBuffer(){
	int i;
	int j;
	//Læser hver karakter
	for(i = 0; i<5; i++){
		
		//Læser hver kolonne
		for(j = 0; j < 5; j++){
			buffer[i][j] = character_data[string[i]-0x20][j];
		}
		buffer[i][5] = 0x00;
	}
}

//Printer 4 bogstaver på skærmen.
void LedUpdatePrint(){
	

	PGOUT = buffer[unitnr][kolonnenr] ;

	switch(kolonnenr){
		case 0: PEOUT = 0x0F; break;
		case 1: PEOUT = 0x17; break;
		case 2: PEOUT = 0x1B; break;
		case 3: PEOUT = 0x1D; break;
		case 4: PEOUT = 0x1E; break;
		case 5: PEOUT = 0x1F; break;
	}
	
	//Tester for unit nr, hvilket display vi er på
	switch (unitnr) {
		case 0:
		  PEOUT |= 0x80;
		  PEOUT &= ~(1 << 7);
		  break;
		case 1:
		  PGOUT |= (1 << 7);
		  PGOUT &= ~(1 << 7);
		  break;
		case 2:
		  PEOUT |= 0x20;
		  PEOUT &= ~(1 << 5);
		  break;
		case 3:
		  PEOUT |= 0x40;
		  PEOUT &= ~(1 << 6);
		  break;
		default:
		  
		  break;
	}
		
	if(unitnr++ == 4){
		unitnr = 0;
		if(kolonnenr++ == 6){
			kolonnenr = 0;
		}
	}
}

void LEDUpdateContinuous(){
	
	int i;
	int j;
	
	//Flytter en kolonne
	if (counter == 100){
		counter = 0;		
		shift++;

		//Flytter displays
		if(shift == 6){
			shift = 0;
			
			//Shifter buffer
			for(i = 0; i < 4; i++){
				for(j = 0; j < 6; j++){
					buffer[i][j] = buffer[i+1][j];
				}
			}
			//Sjekker for enden a string
			if(string[numberShifts] == '\0'){
				numberShifts = 0;
			}

			//Henter inn siste verdi i buffer
			for(j = 0; j < 5; j++){
				buffer[4][j] = character_data[string[numberShifts]-0x20][j];	
			}
			
			//Setter siste søyle i buffer til 0
			buffer[4][5] = 0x00;
			numberShifts++;
		}	

	}

	counter++;

	

	PGOUT = buffer[unitnr][kolonnenr+shift] ;
	// PEOUT = 0x1F & ~(1 << (4-kolonnenr));

	switch(kolonnenr){
		case 0: PEOUT = 0x0F; break;
		case 1: PEOUT = 0x17; break;
		case 2: PEOUT = 0x1B; break;
		case 3: PEOUT = 0x1D; break;
		case 4: PEOUT = 0x1E; break;
		case 5: PEOUT = 0x1F; break;
	}
	
	//Tester for unit nr, hvilket display vi er på
	switch (unitnr) {
		case 0:
		  PEOUT |= 0x80;
		  PEOUT &= ~(1 << 7);
		  break;
		case 1:
		  PGOUT |= (1 << 7);
		  PGOUT &= ~(1 << 7);
		  break;
		case 2:
		  PEOUT |= 0x20;
		  PEOUT &= ~(1 << 5);
		  break;
		case 3:
		  PEOUT |= 0x40;
		  PEOUT &= ~(1 << 6);
		  break;
		default:
		  
		  break;
	}
		
	if(unitnr++ == 4){
		unitnr = 0;
		if(kolonnenr++ == 6){
			kolonnenr = 0;
		}
	}
	
}

/*
void LEDUpdateOnce(){
	
	int i;
	int j;
	
	if (done){
		//LEDSetString();
		LedUpdatePrint();
	}else{
			//Flytter en kolonne
		if (counter == 100){
			counter = 0;		
			shift++;

			//Flytter displays
			if(shift == 6){
				shift = 0;
				
				//Shifter buffer
				for(i = 0; i < 4; i++){
					for(j = 0; j < 6; j++){
						buffer[i][j] = buffer[i+1][j];
					}
				}
				//Sjekker for enden a string
				if(string[numberShifts] == '\0'){
					done = 1;
				}

				//Henter inn siste verdi i buffer
				for(j = 0; j < 5; j++){
					buffer[4][j] = character_data[string[numberShifts]-0x20][j];	
				}
				
				//Setter siste søyle i buffer til 0
				buffer[4][5] = 0x00;
				numberShifts++;
			}	

		}

		counter++;

		PGOUT = buffer[unitnr][kolonnenr+shift] ;
		// PEOUT = 0x1F & ~(1 << (4-kolonnenr));

		switch(kolonnenr){
			case 0: PEOUT = 0x0F; break;
			case 1: PEOUT = 0x17; break;
			case 2: PEOUT = 0x1B; break;
			case 3: PEOUT = 0x1D; break;
			case 4: PEOUT = 0x1E; break;
			case 5: PEOUT = 0x1F; break;
		}
		
		//Tester for unit nr, hvilket display vi er på
		switch (unitnr) {
			case 0:
			  PEOUT |= 0x80;
			  PEOUT &= ~(1 << 7);
			  break;
			case 1:
			  PGOUT |= (1 << 7);
			  PGOUT &= ~(1 << 7);
			  break;
			case 2:
			  PEOUT |= 0x20;
			  PEOUT &= ~(1 << 5);
			  break;
			case 3:
			  PEOUT |= 0x40;
			  PEOUT &= ~(1 << 6);
			  break;
			default:
			  
			  break;
		}
			
		if(unitnr++ == 4){
			unitnr = 0;
			if(kolonnenr++ == 6){
				kolonnenr = 0;
			}
		}
	}//else
	
}
*/
void LEDUpdateOnceAndPrint(){

	
	int i;
	int j;
	
	//Flytter en kolonne
	if (done <= 5 && counter == 100){
		counter = 0;		
		shift++;

		//Flytter displays
		if(shift == 6){
			shift = 0;
			
			//Shifter buffer
			for(i = 0; i < 4; i++){
				for(j = 0; j < 6; j++){
					buffer[i][j] = buffer[i+1][j];
				}
			}
			//Sjekker for enden a string
			if(string[numberShifts] == '\0'){
				numberShifts = 0;
				done = 1;
			}

			//Henter inn siste verdi i buffer
			for(j = 0; j < 5; j++){
				if(done){
					done++;
					buffer[4][j] = character_data[lastString[numberShifts] - 0x20][j];
					
				}else{
					buffer[4][j] = character_data[string[numberShifts]-0x20][j];
				}
					
			}
			
			//Setter siste søyle i buffer til 0
			buffer[4][5] = 0x00;
			numberShifts++;
		}	

	}

	counter++;

	PGOUT = buffer[unitnr][kolonnenr+shift] ;
	// PEOUT = 0x1F & ~(1 << (4-kolonnenr));

	switch(kolonnenr){
		case 0: PEOUT = 0x0F; break;
		case 1: PEOUT = 0x17; break;
		case 2: PEOUT = 0x1B; break;
		case 3: PEOUT = 0x1D; break;
		case 4: PEOUT = 0x1E; break;
		case 5: PEOUT = 0x1F; break;
	}
	
	//Tester for unit nr, hvilket display vi er på
	switch (unitnr) {
		case 0:
		  PEOUT |= 0x80;
		  PEOUT &= ~(1 << 7);
		  break;
		case 1:
		  PGOUT |= (1 << 7);
		  PGOUT &= ~(1 << 7);
		  break;
		case 2:
		  PEOUT |= 0x20;
		  PEOUT &= ~(1 << 5);
		  break;
		case 3:
		  PEOUT |= 0x40;
		  PEOUT &= ~(1 << 6);
		  break;
		default:
		  
		  break;
	}
		
	if(unitnr++ == 4){
		unitnr = 0;
		if(kolonnenr++ == 6){
			kolonnenr = 0;
		}
	}
}


void LEDUpdateOnce(){
	
	int i;
	int j;
	
	if(!done){
		//Flytter en kolonne
		if (counter == 100){
			counter = 0;		
			shift++;

			//Flytter displays
			if(shift == 6){
				shift = 0;
				
				//Shifter buffer
				for(i = 0; i < 4; i++){
					for(j = 0; j < 6; j++){
						buffer[i][j] = buffer[i+1][j];
					}
				}
				//Sjekker for enden a string
				if(string[numberShifts] == '\0'){
					numberShifts = 0;
					done = 1;
				}

				//Henter inn siste verdi i buffer
				for(j = 0; j < 5; j++){
					if(done){
						//buffer[4][j] = 0x00;
						
					}else{
						buffer[4][j] = character_data[string[numberShifts]-0x20][j];
					}
						
				}
				
				//Setter siste søyle i buffer til 0
				buffer[4][5] = 0x00;
				numberShifts++;
			}	

		}

		counter++;
	}
	

	PGOUT = buffer[unitnr][kolonnenr+shift] ;
	// PEOUT = 0x1F & ~(1 << (4-kolonnenr));

	switch(kolonnenr){
		case 0: PEOUT = 0x0F; break;
		case 1: PEOUT = 0x17; break;
		case 2: PEOUT = 0x1B; break;
		case 3: PEOUT = 0x1D; break;
		case 4: PEOUT = 0x1E; break;
		case 5: PEOUT = 0x1F; break;
	}
	
	//Tester for unit nr, hvilket display vi er på
	switch (unitnr) {
		case 0:
		  PEOUT |= 0x80;
		  PEOUT &= ~(1 << 7);
		  break;
		case 1:
		  PGOUT |= (1 << 7);
		  PGOUT &= ~(1 << 7);
		  break;
		case 2:
		  PEOUT |= 0x20;
		  PEOUT &= ~(1 << 5);
		  break;
		case 3:
		  PEOUT |= 0x40;
		  PEOUT &= ~(1 << 6);
		  break;
		default:
		  
		  break;
	}
		
	if(unitnr++ == 4){
		unitnr = 0;
		if(kolonnenr++ == 6){
			kolonnenr = 0;
		}
	}

}
