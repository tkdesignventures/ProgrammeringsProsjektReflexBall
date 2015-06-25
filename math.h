#include "refball.h"
#ifndef _MATH_H_
#define _MATH_H_
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a) * (b) >> FIX14_SHIFT)
#define FIX14_div(a,b)   ( ((a) << FIX14_SHIFT / (b) ))



long sin(int x);
long cos(int x);
void rotate(Ball * ball, int ang);


#endif
