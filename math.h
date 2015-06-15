#ifndef _MATH_H_
#define _MATH_H_

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a) * (b) >> FIX14_SHIFT)
#define FIX14_div(a,b)   ( ((a) << FIX14_SHIFT / (b) ))

struct TVector {
	long x,y;
};

long sin(int x);
long cos(int x);
long ARCSIN(int x);
void rotate(struct TVector *v , int ang);
void initVector(struct TVector *v, long x, long y);
long expand(long i);
void printFix(long i);

#endif
