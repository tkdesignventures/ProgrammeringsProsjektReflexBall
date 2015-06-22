#include <eZ8.h>             // special encore constants, macros and flash routines
#include "refball.h"
#include "graphics.h"
#include "ctimer.h"
#include "keys.h"
#include <sio.h>
#include "ansi.h"
#include "math.h"
#include "menu.h"

int Game(int difficulty);

void main(){
	int selectedOption;
	char key, lastKey, lastKey2;
	int difficulty,victory;
	
	difficulty = 1;
	selectedOption = 1;
	victory = 0;
	
	init_uart(_UART0,_DEFFREQ,_DEFBAUD);
	setTimer();
	initiateMenu();
	
	for(;;){
		key = getKey();
		
		
		//Navigates the menu
		while(key != KEY_RIGHT){
			//Move up
			if(key == KEY_MIDDLE){
				selectedOption++;
			//Move down
			}else if(key == KEY_LEFT){
				selectedOption--;
			}
			if(selectedOption >= 4){
				selectedOption = 1;
			}else if(selectedOption <= 0){
				selectedOption = 3;
			}
			moveMarker(selectedOption);
			
			lastKey = key;
			
			while(key == lastKey){
				key = getKey();
			}
			
		}
		
		if(selectedOption == 1){
			victory = Game(difficulty);
			if(victory){
				drawVictory();
			}else{
				drawGameOver();
			}
			
			initiateMenu();
		}else if(selectedOption == 2){
			difficulty ++;
			if(difficulty >= 4){
				difficulty = 1;
			}
			printDifficulty(difficulty);
		}
		else if(selectedOption == 3){
			printHelp();
		}
		
		lastKey2 = key;
		while(key == lastKey2){
			key = getKey();
		}
	}
	

	
	
}	


int Game(int difficulty){
		
		int i;

  	  	Ball ball;
		Box * box = newBoxStack();
  	  	long strikerx;
	  	char key;
		char lives;
		char waitStart;
  	    unsigned long refreshTime;
    	
    	clrscr();

		  //Initialize
		  lives = 10;
		  strikerx = 30;
		  refreshTime = 100;
		  ball.x = 5 << FIX14_SHIFT;
		  ball.y = 5 << FIX14_SHIFT;
		  ball.outOfBounds = 0;
		  ball.power = 1;
		  waitStart = 1;
	/*
		  //X- and Y-component are set to .707
		  ball.xdir = (-11 << (FIX14_SHIFT - 4));
		  ball.ydir = (-11 << (FIX14_SHIFT - 4));
	*/
		  setBallOverStriker(&ball, strikerx);

      	drawBounds(L_EDGE_COORD,TOP_EDGE_COORD,R_EDGE_COORD,OUT_OF_BOUNDS,0);

		createBoxes(box,1);
		for(i = 0; i < box->size; i++){
			drawBox(box->x[i],box->y[i],box->durability[i]);   
		}


	    drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
		
	

		drawStriker(strikerx,0);
		setTimer();

		gotoxy(R_EDGE_COORD + 5,15);
		printf("Extra lives left: %d    ", (lives + 1));
		gotoxy(R_EDGE_COORD + 5,16);
		printf("Boxes left: %d    ", box->boxesLeft);

        while(lives > 0 && box->boxesLeft > 0){
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
              				drawChar(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y), checkBall(&ball,box,strikerx));
							gotoxy(R_EDGE_COORD + 5,16);
							printf("Boxes left: %d    ", box->boxesLeft);

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
	
	return lives;
}
