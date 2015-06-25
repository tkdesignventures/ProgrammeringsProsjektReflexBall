#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include <stdlib.h>							// special encore serial i/o routines
#include "ansi.h"
#include "math.h"
//Main funktion bruges kun til at teste funktionen af math.
void main(){
struct TVector vektoren;
init_uart(_UART0,_DEFFREQ,_DEFBAUD);

clrscr();
blink(0);
printf("feeuhst\n");
printf("sinus: 45, 90, -90? \n");
printFix(expand(sin(64)));
printf(", ");
printFix(expand(sin(128)));
printf(", ");
printFix(expand(sin(-(int)128)));
printf("\n");
printf("long: %d, %d.\n",sin(128),sin(-(int)128));
initVector(&vektoren,-4,2);
rotate(&vektoren,-50);
printFix(expand(vektoren.x));
printf("\n");
printFix(expand(vektoren.y));


do{} while(1!=2);
}
