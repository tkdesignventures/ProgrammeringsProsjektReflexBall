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

void checkBall(Ball * ball, unsigned char x,Bresenham * b, TVector * nextPos){
  int angleIn;
  int angleIn2;
  int angleOut;
  int yd;

  char right;
	 computeNextPixel(ball,b,nextPos);
   /* unsigned char xt = ball->x;
    unsigned char yt = ball->y;
    unsigned char xtd = toTerminalCoordinates(ball->xdir);
    unsigned char ytd = toTerminalCoordinates(ball->ydir);*/
    if((nextPos->y == STRIKER_Y) && (nextPos->x >= (x - STRIKER_WIDTH)) && nextPos->x <= (x + STRIKER_WIDTH)){


      if(ball->xdir > 0){
        right = 1;
      }else{
        right = 0;
      }
      gotoxy(80,30);
      printf("right: _%d_, xdir: _%d_",right,ball->xdir);
      yd = abs(ball->ydir);
      yd = yd >> 5;
      angleIn = arcsin(yd);
      angleIn2 = 128 - angleIn;

      if(right){
        rotate(ball, (256+128-angleIn));
      }else{
        rotate(ball, (angleIn+128));
      }

      //Left part of striker
      if(nextPos->x >= x - STRIKER_WIDTH && nextPos->x < x){
        if(right){
          rotate(ball,(angleIn2/3));
        }else{
          rotate(ball,- (int)(3*angleIn2));
        }
      //Middle part of striker
      }else if (nextPos->x == x){
        ball->ydir *= -1;
      //Right part of striker
      }else{
        if(right){
          rotate(ball,- (int)(3*angleIn2));
        }else{
          rotate(ball,(angleIn2/3));
        }
      }

      initLine(ball,b);
    }
    else if(nextPos->x >= R_EDGE_COORD || nextPos->x <= L_EDGE_COORD){
      ball->xdir *= -1;
      initLine(ball,b);
    }
    else if(nextPos->y <= TOP_EDGE_COORD){
      ball->ydir *= -1;
      initLine(ball,b);
      }
    else if(nextPos->y >= OUT_OF_BOUNDS){
      gotoxy(20,20);
    printf("Out of bounds");
    }


}
long toTerminalCoordinates(long x){
  	long output = x >> FIX14_SHIFT;
	output += (x >> (FIX14_SHIFT-1)) & 0x1; // Round correctly
	return output;

}

void initLine(Ball * ball, Bresenham * b){
  int w,h;
  long x2 = ball->x + (toTerminalCoordinates(ball->xdir*64));
  long y2 = (ball->y +  (toTerminalCoordinates(ball->ydir*64)));

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

void computeNextPixel(Ball * ball, Bresenham * b, TVector * vector){

    b->numerator += b->shortest;
    if(!( b->numerator < b->longest)){
      b->numerator -= b->longest;
      vector->x = ball->x + b->dx1;
      vector->y = ball->y + b->dy1;
    }
    else{
      vector->x = ball->x + b->dx2;
      vector->y = ball->y + b->dy2;
    }
}
