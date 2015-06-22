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
void setLedMode(char modeIn);


void LEDColumn(char value);
void LEDUpdate();
void LEDSetString(char string1[]);

//Trenger kun at kaldes inden LEDUpdatePrint.
void LEDLoadBuffer();

//Printer 4 bogstaver på skærmen.
void LedUpdatePrint();

void LEDUpdateContinuous();
void LEDUpdateOnceAndPrint();

void LEDUpdateOnce();

#endif
