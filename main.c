#include <eZ8.h>             // special encore constants, macros and flash routines
#include "refball.h"
#include "graphics.h"
#include "ctimer.h"
#include "keys.h"
#include <sio.h>
#include "ansi.h"
#include "math.h"
  void main(){
  	  	Ball ball;
		Box * box = newBoxStack();
  	  	long strikerx;
	  	  char key;
		    char lives;
		    char waitStart;
  	    unsigned long refreshTime;
    		init_uart(_UART0,_DEFFREQ,_DEFBAUD);
    		clrscr();
      //Initialize
	  lives = 2;
      strikerx = 30;
      refreshTime = 100;
      ball.x = 5 << FIX14_SHIFT;
      ball.y = 5 << FIX14_SHIFT;
	  ball.outOfBounds = 0;
	  waitStart = 1;
/*
	  //X- and Y-component are set to .707
      ball.xdir = (-11 << (FIX14_SHIFT - 4));
      ball.ydir = (-11 << (FIX14_SHIFT - 4));
*/
	  setBallOverStriker(&ball, strikerx);

      	drawBounds(L_EDGE_COORD,TOP_EDGE_COORD,R_EDGE_COORD,OUT_OF_BOUNDS);
	//	createBoxes(box,0);
	    drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
	
		drawStriker(strikerx,0);
		setTimer();

		gotoxy(R_EDGE_COORD + 5,15);
		printf("Extra lives left: %d    ", lives);

        while(lives >= 0){
			     	key = getKey();

    				if(key == 1){

					waitStart = 0;
					}

    				else if(key == 2){
      					moveStriker(&strikerx, 1);
	                	moveDrawStriker(strikerx,1);
	                }else if(key == 4){
	      					moveStriker(&strikerx,0);
	                		moveDrawStriker(strikerx,0);
	                 }


					if((getCentis()- GAMESPEED) > refreshTime){

						if(!waitStart){
							refreshTime = getCentis();
              				fixBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),	checkBall(&ball,box,strikerx));
              				if(ball.outOfBounds){
								ball.outOfBounds = 0;
								lives--;
								waitStart = 1;
								gotoxy(R_EDGE_COORD + 5,15);
								printf("Extra lives left: %d    ", lives);
							}
							moveBall(&ball);
							drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);




						}else{
						drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),7);
 					    setBallOverStriker(&ball, strikerx);
						drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
						}


				  }

			}//while

			drawGameOver();

}



		




//Spoersmaal til i morgen:
//0. Hvorfor kan bolden k�re gjennem strikeren
//1. Hvorfor flytter ikke bolden sig - se nr 2.
//2. Hvorfor fungerer ikke setBallOverStriker() - vi proever at shifte en char! HAHA

