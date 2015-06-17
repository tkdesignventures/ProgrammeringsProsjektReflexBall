#include "refball.h"
#include "arcsin.h"
#ifndef _MATH_H_
#define _MATH_H_
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a) * (b) >> FIX14_SHIFT)
#define FIX14_div(a,b)   ( ((a) << FIX14_SHIFT / (b) ))



long sin(int x);
long cos(int x);
int angle(int x);
void rotate(Ball * ball, int ang);
void initVector(TVector *v, long x, long y);
long expand(long i);
void printFix(long i);
int abs(int a);

#endif
