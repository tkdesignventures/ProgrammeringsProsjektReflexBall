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
	
	if(striker.x+ 
	if(direction)
		striker.x +=1;
	else
		striker.x -=1;
}
char isDead()
	return lives >=0;
}

void updateGame(){
	if(gameActive && getCentis()- gameSpeed > gameTime )
	{
			
		
	}
}
