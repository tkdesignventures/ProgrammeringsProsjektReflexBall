#include <eZ8.h>             // special encore constants, macros and flash routines
#include "refball.h"
#include "graphics.h"
#include "ctimer.h"
#include "keys.h"
#include <sio.h>
void main(){
		Ball ball ;
		Striker striker;
		unsigned char gameActive;
		unsigned char lives;
		unsigned long gameTime;
		unsigned char boxesLeft;
		unsigned char waitStart;
		unsigned long refreshTime;
		unsigned char level;
		unsigned char key;
		Box * box = newBoxStack();
		init_uart(_UART0,_DEFFREQ,_DEFBAUD);
		clrscr();

		level = 1;
		waitStart = 1;
		gameTime = 0;
		refreshTime=0;
		gameActive = 1;
		lives = 3;
		initGame(&ball,&striker,box,0);
		setTimer();

		for(;;)
		{
			key = getKey();
				if(key == 1)
					waitStart = 1;
				else if(key == 2)
					moveStriker(&striker, 1);
				else if(key == 4)
					moveStriker(&striker,0);

				if(getCentis()- GAMESPEED >= refreshTime){
					refreshTime = getCentis();
					if(gameActive){
							gameTime += GAMESPEED;
							if(!waitStart){
									drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),7);
									moveBall(&ball);
									drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
									if(!checkBall(&ball, &striker, box){
										lives --;
										waitStart = 0;
									}
									}
							else {
									drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),7);
									setBallOverStriker(&ball,&striker);
									drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
									}

						}

			}

		}
}
