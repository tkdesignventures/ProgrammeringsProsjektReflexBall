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

void checkBall(Ball * ball, unsigned char x){
  int angleIn;
  int angleIn2;
  int angleOut;
  int yd;
  char right;
  char nextPosX, nextPosY;
  nextPosX = toTerminalCoordinates(ball->x + ball->xdir);
  nextPosY = toTerminalCoordinates(ball->y + ball->ydir);
    if((nextPosY == STRIKER_Y) && (nextPosX >= (x - STRIKER_WIDTH)) && nextPosX <= (x + STRIKER_WIDTH)){


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
      if(nextPosX >= x - STRIKER_WIDTH && nextPosX < x){
        if(right){
          rotate(ball,(angleIn2/3));
        }else{
          rotate(ball,- (int)(3*angleIn2));
        }
      //Middle part of striker
      }else if (nextPosX == x){
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
    else if(nextPosX >= R_EDGE_COORD || nextPosX <= L_EDGE_COORD){
      ball->xdir *= -1;
    }
    else if(nextPosY <= TOP_EDGE_COORD){
      ball->ydir *= -1;
      }
    else if(nextPosY >= OUT_OF_BOUNDS){
      gotoxy(20,20);
    printf("Out of bounds");
    }


}
long toTerminalCoordinates(long x){
  	long output = x >> FIX14_SHIFT;
	output += (x >> (FIX14_SHIFT-1)) & 0x1; // Round correctly
	return output;

}
