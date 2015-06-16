#include <eZ8.h>
#include <sio.h>
#include <stdlib.h>
#include "refball.h"
#include "graphics.h"
#include "math.h"
Box * newBoxStack(void) {
    Box * stackContents;
    stackContents = malloc(sizeof(Box));
    stackContents->size = 0;
    stackContents->capacity = 1;
    stackContents->x= malloc(sizeof(char));
    stackContents->y = malloc(sizeof(char));
    stackContents->durability = malloc(sizeof(char));
    stackContents->powertime = malloc(sizeof(char));
    return stackContents;
}

void newBoxStackElement(Box * box){ // Creates a new spot in box array. Prints error if NULL. Only adds 10 a time to avoid using time


      }

void moveBall(Ball * ball){
	ball->x += ball->xdir;
	ball->y += ball->ydir
}

void moveStriker( Striker * striker,unsigned char direction){

	if((striker->x - STRIKER_WIDTH >= L_EDGE_COORD) && (striker->+STRIKER_WIDTH <= R_EDGE_COORD-2)){
		moveDrawStriker(striker->x,STRIKER_Y,direction);
			if(direction)
				striker->x += 1;
			else
				striker->x -= 1;
      }
}


unsigned char checkBall( Ball * ball,  Striker * striker,   Box * box){
    char x,y;
		x = toTerminalCoords(ball->x);
		y = toTerminalCoords(ball->y);
		if(y >= OUT_OF_BOUNDS)
      	     return 0;
		else if(x >= L_EDGE_COORD || x <= R_EDGE_COORD)
			ball->xdir *= -1;

		else if(y <= TOP_EDGE_COORD)
			ball->ydir *=-1;
    else if((x <= striker->x + STRIKER_WIDTH) && ( x >= striker->x - STRIKER_WIDTH))
    ball->ydir*=-1;
		else
			checkBoxes(ball, box);
      return 1;
}

void checkBoxes( Ball * ball,  Box * box){
	int j;
	int xt = toTerminalCoords(ball->x); // husk at snakke koordinater
	int yt = toTerminalCoords(ball->y);
	for(j=0; j < box->capacity; j++){
		if((box->durability[j] > 0) && (box->x[j] == xt || box->x[j] +1 == xt || box->x[j] + 2 == xt) && box->y[j] == yt)  // Boksene har en bredde på 3, vi tester alle koordinater
			{
				if(!(--box->durability[j]))
					drawBox(box->x[j],box->y[j],7);
				}

			}
	}

unsigned char initGame( Ball * ball,  Striker * striker,   Box * box, unsigned char level){

  drawBounds(L_EDGE_COORD,TOP_EDGE_COORD, R_EDGE_COORD, OUT_OF_BOUNDS);
  striker->x = STRIKER_START;
  drawStriker(striker->x,STRIKER_Y,0);
  setBallOverStriker(ball,striker->x);
	drawBall(toTerminalCoords(ball->x),toTerminalCoords(ball->y),0);
  createBoxes(box, level);
}

unsigned char toTerminalCoords(long input){
	unsigned char out;
	out = input >> FIX14_SHIFT;
	out += (input >> (FIX14_SHIFT-1)) & 0x1; // Find lige ud af afrunding
	return out;
}

void setBallOverStriker( Ball * ball,  unsigned char st){
	ball->x = (st << FIX14_SHIFT);
	ball->y = ((STRIKER_Y-OVER_STRIKER) << FIX14_SHIFT);
  ball->xdir = (double)((0.707) << FIX14_SHIFT);
  ball->ydir = (double)((0.707) << FIX14_SHIFT);
}


void createBoxes( Box * box,char level){ //Creates and draws boxes
	unsigned char j,i;

			     for(j=0;j<2;j++){
				         for(i = L_EDGE_COORD + 3; i < (R_EDGE_COORD-3); i+=3){
                      if (box->capacity == box->size) {
                                  box->x = realloc(box->x,(box->capacity+10) *sizeof(char));
                                  box->y = realloc(box->y,(box->capacity+10) *sizeof(char));
                                  box->powertime = realloc(box->powertime,(box->capacity+10) *sizeof(char));
                                  box->durability = realloc(box->durability,(box->capacity+10) *sizeof(char));
                                  box->capacity+=10;

                                  }
                                  box->x[box->size] = i;
                      						box->y[box->size] = TOP_EDGE_COORD+2+j;
                      						box->durability[box->size] = 1;
                                  box->powertime[box->size]=0;
                      						drawBox(box->x[box->size],box->y[box->size],0);
                        box->size++;




                      }
          }
  }
