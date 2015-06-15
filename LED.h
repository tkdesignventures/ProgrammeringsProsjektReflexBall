#ifndef _LED_H_
#define _LED_H_

/*
#pragma interrupt
void timer1int(){
	//LEDUpdateContinuous();
			LEDUpdateOnce();
}
*/

void LEDInit();

void LEDColumn(char value);

//Trenger kun at kaldes inden LEDUpdatePrint.
void LEDSetString(char string[]);

//Printer 4 bogstaver på skærmen.
void LedUpdatePrint();

void LEDUpdateContinuous();


void LEDUpdateOnce();

#endif
