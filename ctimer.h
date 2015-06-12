#ifndef _CTIMER_H_
#define _CTIMER_H

void resetTimer(){
time = 0;
}
#pragma interrupt
timer0int(){
time++;
delay--;
}

int getDelay(){
return delay;
}

void setDelay(int input){
delay = input;
}


void setTimer(){
	char preScale = 0x07<<3;	
	DI();
	T0CTL = 0x01 | preScale;
	T0H = 0x00;
	T0L = 0x01;
	T0RH = 0x05;
	T0RL = 0xA0;
	SET_VECTOR(TIMER0, timer0int);
	IRQ0ENH |= 0x20;
	IRQ0ENL |= 0x20;
	T0CTL |= 0x80;

	EI();
}



#endif
