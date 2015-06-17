#include <eZ8.h>
#include <sio.h>
#include "refball.h"
#include "math.h"
#include "graphics.h"
#include "ansi.h"

void moveBall(Ball * ball){
  ball->x += ball->xdir;
  ball->y += ball->ydir;
}

void moveStriker(char * x,char direction){
    if(direction && ((*x + STRIKER_WIDTH+1) <R_EDGE_COORD))
        * x += 1;

    else if(!direction && ((*x - STRIKER_WIDTH-1) > (L_EDGE_COORD)))
        * x -= 1;
}

void checkBall(Ball * ball, unsigned char x,Bresenham * b){
    unsigned char xt = ball->x;
    unsigned char yt = ball->y;
    unsigned char xtd = toTerminalCoordinates(ball->xdir);
    unsigned char ytd = toTerminalCoordinates(ball->ydir);
    if(()(yt+ytd) >= STRIKER_Y) && ()(xt+xtd) >= x-2) && xt+xtd <= x+2){
      ball->ydir *=-1;
      initLine(ball,b);
      }
    else if(xt + xtd >= R_EDGE_COORD || xt+xtd <= L_EDGE_COORD){
      ball->xdir *= -1;
      initLine(ball,b);
    }
    else if(yt+ytd <= TOP_EDGE_COORD){
      ball->ydir *= -1;
      initLine(ball,b);
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

void initLine(Ball * ball, Bresenham * b){
  int w,h;
  long x2 = toTerminalCoordinates((ball->xdir << 7));
  long y2 = toTerminalCoordinates((ball->ydir<<7));
  b->dx1 = 0;
  b->dy1 = 0;
  b->dx2 = 0;
  b->dy2 = 0;
  w = x2-ball->x;
  h = x2-ball->y;
    if(w<0)
      b->dx1 = -1;
    else if(w>0)
      b->dx1=1;
    if(h<0)
      b->dy1 = -1;
    else if(h>0)
      b->dy1=1;
    if(w<0)
      b->dx2 = -1;
    else if(w>0)
      b->dx2=1;
    b->longest = abs(w);
    b->shortest = abs(h);
      if(!(longest>shortest)){
        longest = abs(h);
        shortest = abs(w);
        b->dx2=0;
        if(h<0)
            b->dy2 = -1;
        else if(h>0)
            b->dy2=1;
        }
    b->numerator = longest >> 1;
}

void computeNextPixel(Ball * ball, Bresemham * b){
    b->numerator += shortest;
    if(!( b->numerator < b->longest)){
      b->numerator -= longest;
      ball->x += b->dx1;
      ball->y += b->dy1;
    }
    else{
      ball->x += b->dx2;
      ball->y += b->dy2;
    }
}
