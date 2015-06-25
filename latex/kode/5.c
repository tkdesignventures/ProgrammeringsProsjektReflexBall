#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "ansi.h"
#include "keys.h"
//Laver structure time
struct time {
	unsigned char h,m,s,hs;

};
struct time tid;
//Opdaterer tiden.
#pragma interrupt
void timer0int(){
	tid.hs++; 
	if(tid.hs == 100){
		tid.s++;
		tid.hs=0;
	
	
		if(tid.s == 60){
		tid.m++;
		tid.s=0;
		if(tid.m == 60){
		tid.h++;
		tid.m=0;
	}}
	//Skrevet indenfor ifløkken som opdateres hvert sekund, sådan at tiden skrives hvert sekund. 
	gotoxy(2,2);
	printf("Time: %02d:%02d:%02d",tid.h,tid.m,tid.s);
	}

}

void setTimer(){
	char preScale = 0x07<<3;	
	DI();
	T0CTL = 0x01 | preScale;
	T0H = 0x00;
	T0L = 0x01;
	T0RH = 0x05; //Sætter reload sådan, at den tæller hvert 100 del af et sekund.
	T0RL = 0xA0;
	SET_VECTOR(TIMER0, timer0int);
	IRQ0ENH |= 0x20; //høj prioritet
	IRQ0ENL |= 0x20;
	T0CTL |= 0x80; //enable count

	EI();
}
//Stopper timeren
void stop(){
	DI();
	T0CTL &= 0x7F;

}

void main(){
char key;
init_uart(_UART0,_DEFFREQ,_DEFBAUD);
tid.h=0;
tid.m,tid.s,tid.hs=0;
clrscr();
window(1,1,10,25,1,"Stopur");
setTimer();

while(1 != 2){
//Keys realiserer de forskellige funktioner i timeren
key=getKey();
	if(key==6){
	//resetter timeren
		stop();	
		tid.h=0;
		tid.m=0;
		tid.s=0;
		tid.hs=0;
		gotoxy(2,2);
		printf("Time: %02d:%02d:%02d",tid.h,tid.m,tid.s);
}
	else if(key==4){
	//Skriver splittime2
		gotoxy(4,2);
		printf("Splittime2: %02d:%02d:%02d",tid.h,tid.m,tid.s);
	}
	else if (key==2){
	Skriver splittime1
		gotoxy(3,2);
		printf("Splittime1: %02d:%02d:%02d",tid.h,tid.m,tid.s);
		}
	else if (key==1){
	//Starter/stopper uret
		if((T0CTL & 0x80) == 0x80){
			stop();
		} else{
			T0CTL|=0x80;
			EI();
		}
	}}}





