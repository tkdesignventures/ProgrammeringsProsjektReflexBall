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
    if(((yt+ytd) >= STRIKER_Y) && ((xt+xtd) >= x-2) && xt+xtd <= x+2){
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
  	long output = x >> FIX14_SHIFT;
	output += (x >> (FIX14_SHIFT-1)) & 0x1; // Round correctly
	return output;

}

void initLine(Ball * ball, Bresenham * b){
  int w,h;
  long x2 = ball->x + (toTerminalCoordinates(ball->xdir)*100);
  long y2 = (ball->y +  (toTerminalCoordinates(ball->ydir)*100));

  gotoxy(30,30);
  printf("%d:%d",x2,y2);

  b->dx1 = 0;
  b->dy1 = 0;
  b->dx2 = 0;
  b->dy2 = 0;
  w = x2-ball->x;
  h = y2-ball->y;
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
      if(!(b->longest > b->shortest)){
        b->longest = abs(h);
        b->shortest = abs(w);
        b->dx2=0;
        if(h<0)
            b->dy2 = -1;
        else if(h>0)
            b->dy2=1;
        }
    b->numerator = b->longest >> 1;
}
 
void computeNextPixel(Ball * ball, Bresenham * b){
    b->numerator += b->shortest;
    if(!( b->numerator < b->longest)){
      b->numerator -= b->longest;
      ball->x += b->dx1;
      ball->y += b->dy1;
    }
    else{
      ball->x += b->dx2;
      ball->y += b->dy2;
    }
}
