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

void moveStriker(long * x,char direction){
    if(direction && ((*x + STRIKER_WIDTH+1) <R_EDGE_COORD))
        * x += 1;

    else if(!direction && ((*x - STRIKER_WIDTH-1) > (L_EDGE_COORD)))
        * x -= 1;
}

void checkBall(Ball * ball, int x){
  int angleIn;
  int angleIn2;
  int angleOut;
  long yd;
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
     
		
	  	ball->ydir *= -1;

	  	//Left part of striker
		if(nextPosX >= x - STRIKER_WIDTH && nextPosX < x){
        	if(right){
				rotate(ball, -(int)43);
			}else{
				rotate(ball, (int)43);
			}	

      	//Middle part of striker
      	}else if (nextPosX == x){
        
      	//Right part of striker
      	}else{
       		if(right){
				rotate(ball, (int)43);
			}else{
				rotate(ball, -(int)43);
			}
		}


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

void setBallOverStriker( Ball * ball, long st){
	ball->x = (st << FIX14_SHIFT);
	ball->y = ((STRIKER_Y-OVER_STRIKER) << FIX14_SHIFT);
	
  ball->xdir = (-11 << (FIX14_SHIFT - 4));
  ball->ydir = (-11 << (FIX14_SHIFT - 4));


}
