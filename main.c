#include <eZ8.h>             // special encore constants, macros and flash routines
#include "refball.h"
#include "graphics.h"
#include "ctimer.h"
#include "keys.h"

void main(){
		struct Box box[];
		struct Ball ball ;
		struct Striker striker;
		unsigned char gameActive;
		unsigned char lives;
		unsigned long gameTime;
		unsigned char boxesLeft;
		unsigned char waitStart;
		unsigned long refreshTime;

		waitStart = 0;
		gameTime = 0;
		refreshTime=0;
		gameActive = 1;
		lives = 3;
		boxesLeft = initGame();
		setTimer();

		for(;;)
		{
			if(getCentis()- GAMESPEED >= refreshTime){
				updateGame();
			}

		}

}


	long updateGame() {
		if(getCentis()- GAMESPEED >= refreshTime )
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
					return
	}
