#include "lut.h"
#include "math.h"
#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
long sin(int x){
	return SIN[0x01FF & x];
}

long cos(int x){
return sin(x+128);
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
void initVector(struct TVector *v, long x, long y){
v->x = x << FIX14_SHIFT;
v->y = y << FIX14_SHIFT;
}
void rotate(struct TVector *v , int ang){
	int sinA = sin(ang);
	int cosA = cos(ang);
	long tempX = v->x;
	

	v->x = FIX14_MULT(tempX,cosA) - FIX14_MULT(v->y,sinA);
	v->y = FIX14_MULT(tempX,sinA) + FIX14_MULT(v->y,cosA);
}

