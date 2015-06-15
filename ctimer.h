#ifndef _CTIMER_H_
#define _CTIMER_H

void resetTimer();
void timer0int();
int getDelay();
void setDelay(int input);
void setTimer();
unsigned long getCentis();
#endif
