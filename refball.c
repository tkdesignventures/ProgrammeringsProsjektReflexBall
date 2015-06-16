#include <eZ8.h>
#include <sio.h>
#include "refball_h"
#include "math.h"
#include "graphics.h"

void moveBall(Ball * ball){
  ball->x += ball->xdir;
  ball->y += ball->ydir;
}

void moveStriker(char * x,direction){
    if(direction && ((*x + STRIKER_WIDTH+1) <R_EDGE_COORD))
        * x += 1;

    else if(!direction && ((*x - STRIKER_WIDTH-1) > (L_EDGE_COORD)))
        * x -= 1;
}

void checkBall(Ball * ball, unsigned char x){
    unsigned char xt = toTerminalCoordinates(ball->x);
    unsigned char yt = toTerminalCoordinates(ball->y);
    unsigned char xtd = toTerminalCoordinates(ball->xdir);
    usigned char ytd = toTerminalCoordinates(ball->ydir);
    if(yt+ytd >= STRIKER_Y && xt+xtd >= x-2 && xt+xtd =< x+2){
      ball->ydir *=-1;
      }
    else if(xt + xtd >= R_EDGE_COORD || xt+xtd <= L_EDGE_COORD){
      ball->xdir *= -1;
    }
    else if(yt+ytd <= TOP_EDGE_COORD){
      ball->ydir *= -1;
      }
    else if(yt >= OUT_OF_BOUNDS){
      gotoxy(20,20);
    printf("You dead motherfucker!");
    }


}
long toTerminalCoordinates(long x){
  unsigned char output = x >> FIX14_SHIFT;
	output += (x >> (FIX14_SHIFT-1)) & 0x1; // Round correctly
	return output;

}
