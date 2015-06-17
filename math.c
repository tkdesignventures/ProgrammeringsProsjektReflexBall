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
long angle(int y){
	return ARCSIN[y];
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

//vanlig kommatal ind
void initVector(TVector *v, long x, long y){
v->x = x << FIX14_SHIFT;
v->y = y <<FIX14_SHIFT;
}
void rotate(Ball * ball , int ang){
	int sinA = sin(ang);
	int cosA = cos(ang);
	long tempX = ball->xdir;
	ball->xdir; = FIX14_MULT(tempX,cosA) - FIX14_MULT(v->y,sinA);
	ball->ydir = FIX14_MULT(tempX,sinA) + FIX14_MULT(v->y,cosA);
}
int abs(int a){
	if (a < 0)
	return -a;
	else
	return a;
}
