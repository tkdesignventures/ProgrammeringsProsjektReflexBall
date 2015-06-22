#include <eZ8.h>
#include <sio.h>
#include <stdlib.h>
#include "refball.h"
#include "math.h"
#include "graphics.h"
#include "ansi.h"

void moveBall(Ball * ball){
  ball->x += 2*(ball->xdir);
  ball->y += 2*(ball->ydir);
}

void moveStriker(long * x,char direction){
    if(direction && ((*x + STRIKER_WIDTH+1) <R_EDGE_COORD))
        * x += 2*1;

    else if(!direction && ((*x - STRIKER_WIDTH-1) > (L_EDGE_COORD)))
        * x -= 2*1;
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

        for(j=0; j < box->size; j++){

          if((box->durability[j] > 0) && (nextPosX >= box->x[j] && nextPosX < box->x[j]+BOXSIZE) && (box->y[j] == nextPosY || box->y[j] == yt+1))  // Boksene har en bredde på 3, vi tester alle koordinater
              {
				
			    if(ball->power == 0){
	                if((xt >= box->x[j]) && (xt < box->x[j]+BOXSIZE))
	                ball->ydir *= -1;
	
	                else if(yt == box->y[j] || yt == box->y[j]+1)
	                ball->xdir *= -1;
	
	                else{
	                  ball->xdir *= -1;
	                  ball->ydir *= -1;
	                }
				}
	            if(!(--box->durability[j])){
					box->boxesLeft--;

            	drawBox(box->x[j],box->y[j],7);
				}
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

Box * newBoxStack() {
    Box * stackContents;
    stackContents = malloc(sizeof(Box));
    stackContents-> size = 0;
    stackContents->x= malloc(sizeof(char)*MAX_BOXES);
    stackContents->y = malloc(sizeof(char)*MAX_BOXES);
    stackContents->durability = malloc(sizeof(char)*MAX_BOXES);
    return stackContents;
}

void createBoxes( Box * box,char level){ //Creates and draws boxes
	unsigned char j,i;
  unsigned char * xtemp, * ytemp, * dtemp;
				box->size = 0;
				if(level == 1){
				     for(j=0;j<1;j++){
					        for(i = L_EDGE_COORD + 5; i < L_EDGE_COORD+6;i+=BOXSIZE){//(R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        box->x[box->size] = i;
	                      	box->y[box->size] = TOP_EDGE_COORD+4+j*2;
	                      	box->durability[box->size] = 1;
	                      	box->size++;
							
	                      }
	         		 }
				 }else if(level == 2){
				     for(j=0;j<2;j++){
					         for(i = L_EDGE_COORD + 5; i < L_EDGE_COORD+6;i+=BOXSIZE){//(R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+4+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }

				}else if(level == 3){
				     for(j=0;j<3;j++){
					         for(i = L_EDGE_COORD + 5; i < L_EDGE_COORD+6;i+=BOXSIZE){//(R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+4+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }

				}else if(level == 4){
				     for(j=0;j<4;j++){
					         for(i = L_EDGE_COORD + 5; i < L_EDGE_COORD+6;i+=BOXSIZE){//(R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+4+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }

				}else if(level == 5){
				     for(j=0;j<5;j++){
					         for(i = L_EDGE_COORD + 5; i < L_EDGE_COORD+6;i+=BOXSIZE){//(R_EDGE_COORD-5); i+=BOXSIZE){
						
	                        	box->x[box->size] = i;
	                      		box->y[box->size] = TOP_EDGE_COORD+4+j*2;
	                      		box->durability[box->size] = j+1;
	                      		box->size++;
	
	                      }
	         		 }

				}
					


				 
				box->boxesLeft = box->size;
				


  }
