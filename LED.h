#ifndef _LED_H_
#define _LED_H_

void timer1int();

void LEDInit();

void setLedMode(char modeIn);

void setValue(char valueIn);

void LEDUpdate();

void LEDColumn();

void LEDSetString(char *string1);

void LEDUpdateOnce();

void LEDLoadBuffer();

void LEDUpdatePrint();

#endif
