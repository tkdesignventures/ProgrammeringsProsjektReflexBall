#include "lut.h"
#include "math.h"
#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "refball.h"

long sin(int x){
	return SIN[0x01FF & x];
}

long cos(int x){
	return sin(x+128);
}

int arcsin(int y){
char sign = 1;

/*
	while(y >= 512){
		y -= 512;
	}
	while(y < 0){
		y += 512;
	}

*/
if(y < 0){
	sign = -1;
}
	return (sign * ARCSIN[0x01FF & y]);
}


void printFix(long i){
	if ((i & 0x80000000) !=0) {
		printf("-");
		i = ~i+1;
	}
	printf("%ld.%04ld",i>>16, 10000*(unsigned long) (i & 0xffff)>>16);
}

long expand(long i){
	return i<<2;
}

void rotate(Ball * ball , int ang){
	long sinA = sin(ang);
	long cosA = cos(ang);
	long tempX = ball->xdir;
	ball->xdir = (FIX14_MULT(tempX,cosA) - FIX14_MULT(ball->ydir,sinA));
	ball->ydir = (FIX14_MULT(tempX,sinA) + FIX14_MULT(ball->ydir,cosA));
}
/*
long abs(long a){
	if (a < 0)
	return -a;
	else
	return a;
}
*/
