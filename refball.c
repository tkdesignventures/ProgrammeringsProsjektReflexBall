#include <eZ8.h>             // special encore constants, macros and flash routines
#include "refball.h"
#include "graphics.h"

void moveBall(struct Ball * ball){
	ball->x += ball->xdir;
	ball->y += ball->ydir;
}

void moveStriker(struct Striker * striker,unsigned char direction){

	if((striker->x - STRIKER_WIDTH >= L_EDGE_COORD) && (striker->+STRIKER_WIDTH <= R_EDGE_COORD)){
		moveDrawStriker(striker->x,STRIKER_Y,direction);
			if(direction)
				striker->x += 1;
			else
				striker->x -= 1;
}


unsigned char checkBall(struct Ball * ball, struct Striker * striker,  struct Box * box, int size){
    char x,y;
		x = toTerminalCoords(ball->x);
		y = toTerminalCoords(ball->y);
		if(y >= OUT_OF_BOUNDS)
      	     return 0;
		else if(x => L_EDGE_COORD || x =< R_EDGE_COORD)
			ball->xdir = -(ball->xdir);

		else if(y <= TOP_EDGE_COORD)
			ball->ydir = -(ball->ydir);
    else if((x <= striker->x + STRIKER_WIDTH) && ( x => striker->x - STRIKER_WIDTH))
    ball-> ydir = -(ball->ydir);
		else
			checkBoxes(ball, box, size);
      return 1;
}

void checkBoxes(struct Ball * ball, struct Box * box, int size){
	int j;
	int xt = toTerminalCoords(ball->x); // husk at snakke koordinater
	int yt = toTerminalCoords(ball->y);
	for(j=0; j < size; j++){
		if((box->durability > 0) && (box-> x == xt || box->x +1 == xt || box->x + 2 == xt) && box->y == yt)  // Boksene har en bredde på 3, vi tester alle koordinater
			{
				if(!(--box->durability))
					drawBox(box->x,box->y,7);
				}

			}
			box++;
	}
}

unsigned char initGame(struct Ball * ball, struct Striker * striker,  struct Box * box, unsigned char level){

  drawBounds(L_EDGE_COORD,TOP_EDGE_COORD, R_EDGE_COORD, TOP_EDGE_COORD);
  striker->x = STRIKER_START;
  striker->y = STRIKER_Y;
  drawStriker(striker->x,STRIKER_Y,0);
  setBallOverStriker(ball,striker);
	drawBall(toTerminalCoords(ball->x),toTerminalCoords(ball->y),0);
  return 	createBoxes(box, lev);
}

unsigned char toTerminalCoords(long input){
	unsigned char out;
	out = input >> FIX14_SHIFT;
	out += (input >> (FIX14_SHIFT-1)) & 0x1; // Find lige ud af afrunding
	return out;
}

void setBallOverStriker(struct Ball * ball, struct Striker * striker){
	ball->x = striker->x;
	ball->y = OVER_STRIKER+STRIKER_Y;
	ball->ydir = 0.7071067810 << FIX14_SHIFT;
	ball->xdir = 0.7071067810 << FIX14_SHIFT;
}


unsigned char createBoxes(struct Box * box,char level){ //Creates and draws boxes
	unsigned char j,i;
	unsigned char k = 0;
  unsigned char boxes = 0;
	switch(level){
		case 1 :
			for(j=0;j<2;j++){
				for(int i = L_EDGE_COORD + 3; i < ((R_EDGE_COORD-3); i+=3){
						box->x = i;
						box->y =TOP_EDGE_COORD+2+j;
						box->durability = 1;
            box->powertime=0;
						drawBox(i,j,0);
						box++;
            boxes++;
				}
			}
			break;
		}

		case 2 :
		//Code
		break;

		case 3 :
		//Code
		break;
  return boxes;
}
