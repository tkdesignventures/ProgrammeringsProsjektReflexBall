#ifndef _LED_H_
#define _LED_H_

void timer1int();

void LEDInit();

void setLedMode(char modeIn);

void LEDUpdate();

void LEDSetString(char *string1);

void LEDUpdateOnce();

void LEDLoadBuffer();

void LEDUpdatePrint();

#endif
