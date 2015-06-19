#include <eZ8.h>
#include <sio.h>
#include <stdlib.h>
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

unsigned char checkBall(Ball * ball,Box * box,  int x){
  int angleIn;
  int angleIn2;
  int angleOut;
  long yd;
  char right;
  char nextPosX, nextPosY;
  unsigned char j;
  unsigned char xt = toTerminalCoordinates(ball->x);
  unsigned char yt = toTerminalCoordinates(ball->y);
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
		ball->outOfBounds = 1;
    }

    else{

        for(j=0; j < box->capacity; j++){

          if((box->durability[j] > 0) && (nextPosX >= box->x[j] && nextPosX < box->x[j]+BOXSIZE) && (box->y[j] == nextPosY || box->y[j] == nextPosY+1))  // Boksene har en bredde på 3, vi tester alle koordinater
              {

                if((xt >= box->x[j]) && (xt < box->x[j]+BOXSIZE))
                ball->ydir *= -1;

                else if(yt == box->y[j] || yt == box->y[j]+1)
                ball->xdir *= -1;

                else{
                  ball->xdir *= -1;
                  ball->ydir *= -1;
                }
            if(!(--box->durability[j]))
            drawBox(box->x[j],box->y[j],7);
            }
        }

      }
    if (xt == L_EDGE_COORD || xt == R_EDGE_COORD){
      return EDGE;
    }
    else if(yt == TOP_EDGE_COORD){
      return TOP_EDGE;
    }
    else if(xt == x && yt ==STRIKER_Y){
      return STRIKER;
    }
    else
      return BLANK;

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

Box * newBoxStack(void) {
    Box * stackContents;
    stackContents = malloc(sizeof(Box));
    stackContents-> size = 0;
    stackContents-> capacity = 1;
    stackContents->x= malloc(sizeof(char));
    stackContents->y = malloc(sizeof(char));
    stackContents->durability = malloc(sizeof(char));
    return stackContents;
}

void createBoxes( Box * box,char level){ //Creates and draws boxes
	unsigned char j,i;
  char * xtemp, * ytemp, * dtemp;

			     for(j=0;j<2;j++){
				         for(i = L_EDGE_COORD + 5; i < (R_EDGE_COORD-5); i+=BOXSIZE){
                        if (box->capacity == box->size) {
                                    xtemp = realloc(box->x,(box->capacity+10) *sizeof(char));
                                    ytemp= realloc(box->y,(box->capacity+10) *sizeof(char));
                                    dtemp->durability = realloc(box->durability,(box->capacity+10) *sizeof(char));
                                    box->capacity+=10;
                                    if(xtemp == NULL || ytemp == NULL || dtemp == NULL ){
                                      gotoxy(30,30);
                                      printf("ERROR!!\n");

                                    }
                                    box->x = xtemp;
                                    box->y = ytemp;
                                    box->durability = dtemp;
                                    }
                        box->x[box->size] = i;
                      	box->y[box->size] = TOP_EDGE_COORD+4+j*2;
                      	box->durability[box->size] = 1;
                      	drawBox(box->x[box->size],box->y[box->size],0);
                        box->size++;

                      }
          }
  }
