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

void rotate(Ball * ball , int ang){
	long sinA = sin(ang);
	long cosA = cos(ang);
	long tempX = ball->xdir;
	ball->xdir = (FIX14_MULT(tempX,cosA) - FIX14_MULT(ball->ydir,sinA));
	ball->ydir = (FIX14_MULT(tempX,sinA) + FIX14_MULT(ball->ydir,cosA));
}
