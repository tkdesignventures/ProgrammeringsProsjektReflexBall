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
			if(direction)
				striker.x += STRIKER_SPEED;
			else
				striker.x -= STRIKER_SPEED;
		}
	}

char isAlive(){
	return lives >=0;
}

void updateGame() {
	if(gameActive && getCentis()- GAMESPEED > gameTime )
	{
		gameTime = getCentis();
		drawStriker(striker.xlast,7); // Deletes the last striker
		drawStriker(striker.x,0); // Draws a new striker
		striker.xlast = striker.x;
		moveBall();
		checkBall();

	}

}


void checkBall(){
char x,y;
	if(gameActive)
	{
		x = toTermCords(ball.x);
		y = toTermCords(ball.y);
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
	int x = toTerminalCoords(ball.x); // husk at snakke koordinater
	int y = toTerminalCoords(ball.y);
	size = 5;
	for(j=0; j < size; j++){
		if((box[i].x == x || box[i].x+1 == x || box[i] .x+2 == x) && box[i].y == y) // Boksene har en bredde på 3, vi tester alle koordinater
			{
				if(!(--box[i].durability)){
					boxesleft--;

				}


			}
	}
}

void initGame(unsigned char l, unsigned char diff, unsigned char lev){
	gameActive = 0;
	lives = l;
	level = lev;
	striker . x = STRIKER_START;
	striker . xlast = x;
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
