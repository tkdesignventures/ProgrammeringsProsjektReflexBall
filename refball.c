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
unsigned long gameTime;
unsigned char boxesLeft;
unsigned char waitStart; // Waits for user input to start the game. The ball is placed over the striker when it's true
unsigned long refreshTime;

void moveBall(){
	ball.x += ball.xdir;
	ball.y += ball.ydir;
}

void moveStriker(unsigned char direction){

	if((striker.x - STRIKER_WIDTH >= L_EDGE_COORD) && (striker.x+STRIKER_WIDTH <= R_EDGE_COORD)){
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
	if(getCentis()- GAMESPEED > gameTime )
	{
		refreshTime = getCentis();
		if(gameActive){
			gameTime += GAMESPEED;
				if(!waitStart){
						drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),7);
						moveBall();
						drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
						checkBall();
						}
				else {
						drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),7);
						setBallOverStriker();
						drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
						}
				}
}


void checkBall(){
char x,y;

		x = toTerminalCoords(ball.x);
		y = toTerminalCoords(ball.y);
		if(y == OUT_OF_BOUNDS){
		lives--;
		setBallOverStriker();

		}
		else if(x => L_EDGE_COORD || x =< R_EDGE_COORD)
			ball.xdir = -(ball.xdir);

		else if(y <= TOP_EDGE_COORD)
			ball.ydir = -(ball.ydir);
		else
			checkBoxes();
}

void checkBoxes(){
	int size;
	int j;
	int xt = toTerminalCoords(ball.x); // husk at snakke koordinater
	int yt = toTerminalCoords(ball.y);
	size = sizeof(box)/sizeof(box[0]);
	for(j=0; j < size; j++){
		if((box[i].durability > 0) && (box[i].x == xt || box[i].x +1 == xt || box[i].x + 2 == xt) && box[i].y == yt)  // Boksene har en bredde på 3, vi tester alle koordinater
			{
				if(!(--box[i].durability))
					boxesLeft--;
					drawBox(box[i].x,box[i].y,7);
				}

			}
	}
}

void initGame(unsigned char l, unsigned char diff, unsigned char lev){
	gameActive = 0;
	waitStart = 1;
	boxesLeft = 0;
	lives = l;
	striker.x = STRIKER_START;
	setBallOverStriker();
	createBoxes(lev);
	//drawBackground;
	drawBounds(L_EDGE_COORD,TOP_EDGE_COORD, R_EDGE_COORD, TOP_EDGE_COORD)
	drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
	drawStriker(striker.x,0);

}
void pause(){
gameActive = !gameActive; //Pause or unpause the game
}
unsigned char toTerminalCoords(long input){
	unsigned char out;
	out = input >> FIX14_SHIFT;
	out += (input >> (FIX14_SHIFT-1)) & 0x1; // Find lige ud af afrunding
	return out;
}

void setBallOverStriker(){
	waitStart = 1;
	ball.x = striker.x;
	ball.y = OVER_STRIKER+STRIKER_Y;
	ball.ydir = 1 << FIX14_SHIFT;
	ball.xdir = 0;
}

void startBall(){
	waitStart = 0;
}

void createBoxes(char level){
	unsigned char j,i;
	unsigned char k = 0;
	switch(level){
		case 1 :
			for(j=0;j<2;j++){
				for(int i = L_EDGE_COORD + 3; i < ((R_EDGE_COORD-3)-(L_EDGE_COORD+3)); i+=3){
						box[boxesLeft].x = i;
						box[boxesLeft].y =TOP_EDGE_COORD+2+j;
						box[boxesLeft].durability = 1;
						drawBox(i,j,0);
						boxesLeft++;
				}
			}
			break;
		}


		}
		case 2 :
		//Code
		break;

		case 3 :
		//Code
		break;
	}
}
