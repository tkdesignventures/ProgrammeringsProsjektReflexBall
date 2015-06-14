#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>
#include "refball.h"
#include "timer.h"
#include "graphics.h"


struct Box box[];
struct Ball ball ;
struct Striker striker;
unsigned char gameActive;
unsigned char lives;
unsigned char level;
unsigned long gameTime;
unsigned char boxesleft;

void moveBall(){
	if(gameActive){
	ball.x += ball.xdir;
	ball.y += ball.ydir;
	}
}

void moveStriker(unsigned char direction){

	if(gameActive && (striker.x - STRIKER_WIDTH >= L_EDGE_COORD) && (striker.x+STRIKER_WIDTH <= R_EDGE_COORD)){
		moveDrawStriker(striker.x,direction);
			if(direction)
				striker.x += 1;
			else
				striker.x -= 1;
	}
}

char isAlive(){
	return lives >=0;
}

void updateGame() {
	if(gameActive && getCentis()- GAMESPEED > gameTime )
	{
		gameTime = getCentis();
		moveBall();
		checkBall();

	}

}


void checkBall(){
char x,y;
	if(gameActive)
	{
		x = toTerminalCoords(ball.x);
		y = toTerminalCoords(ball.y);
		if(y == OUT_OF_BOUNDS){
		lives--;
		setBall();
		}
		else if(x => L_EDGE_COORD || x =< R_EDGE_COORD)
			ball.xdir = -(ball.xdir);

		else if(y <= TOP_EDGE_COORD)
			ball.ydir = -(ball.ydir);
		else
			checkBoxes();
	}



}

void checkBoxes(){
	int j;
	int xt = toTerminalCoords(ball.x); // husk at snakke koordinater
	int yt = toTerminalCoords(ball.y);
	size = sizeof(box)/sizeof(box[0]);
	for(j=0; j < size; j++){
		if((box[i].durability > 0) && (box[i].x == xt || box[i].x +1 == xt || box[i].x + 2 == xt) && box[i].y == yt)  // Boksene har en bredde på 3, vi tester alle koordinater
			{
				if(!(--box[i].durability))
					boxesleft--;
					drawBox(box[i].x,box[i].y,7);
				}

			}
	}
}

void initGame(unsigned char l, unsigned char diff, unsigned char lev){
	gameActive = 0;
	lives = l;
	level = lev;
	striker.x = STRIKER_START;
	striker.xlast = striker.x;
	setBallOverStriker();
	createBoxes();
	drawBackground;
	drawBounds(L_EDGE_COORD,TOP_EDGE_COORD, R_EDGE_COORD, TOP_EDGE_COORD)
	drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
	drawStriker(striker.x,0);

}
void pause(){
gameActive = !gameActive; //Pause or unpause the game
}
unsigned char toTerminalCoords(long input){
	unsigned char out;
	out = input >> FIX14_SHIFT
	out += (input >> (FIX14_SHIFT-1)) & 0x1; // Find lige ud af afrunding
	return out;
}
