#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h> 
#include "refball.h"

struct Box * box;
struct Ball * ball;
struct Striker * striker;
unsigned char gameActive;
unsigned char lives;
unsigned char level;
long gameTime;
void moveBall(){
	if(gameActive){
	ball.x += ball.xdir;
	ball.y += ball.ydir;
	}
}

void moveStriker(unsigned char direction){
	
	if((striker->x - STRIKER_WIDTH >= L_EDGE_COORD) && (striker->x+STRIKER_WIDTH <= R_EDGE_COORD)){
			if(direction)
				striker->x +=1;
			else
				striker->x -=1;
		}
	}

char isDead()
	return lives >=0;
}

void updateGame()
	if(gameActive && getCentis()- gameSpeed > gameTime )
	{
		drawStriker(striker->xlast,7)
		striker->xlast = striker->x;
		drawStriker(striker->x,0);
		moveBall();
		checkBall();			
	}
}

