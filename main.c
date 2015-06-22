#include <eZ8.h>             // special encore constants, macros and flash routines
#include "refball.h"
#include "graphics.h"
#include "ctimer.h"
#include "keys.h"
#include <sio.h>
#include "ansi.h"
#include "math.h"
#include "menu.h"
#include "LED.h"

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
	printDifficulty(difficulty);
	
	LEDInit();
	LEDSetString("Welcome     ");
	setLedMode(2);
	//LEDLoadBuffer();
	
	
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
				LEDSetString("Victory    ");
				setLedMode(2);
				drawVictory();
			}else{
				drawGameOver();
				LEDSetString("Game over. Try again.    ");
				setLedMode(2);
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
		char key, lives, level, pause;
		char waitStart;
  	    unsigned long refreshTime;
    	
		
    	clrscr();

		  //Initialize
		  level = 1;
		  lives = 1;
		  strikerx = 30;
		  refreshTime = 100;
		  ball.x = 5 << FIX14_SHIFT;
		  ball.y = 5 << FIX14_SHIFT;
		  ball.outOfBounds = 0;
		  ball.power = 0;
		  pause = 0;
		 
		 
		  
		  drawBounds(L_EDGE_COORD,TOP_EDGE_COORD,R_EDGE_COORD,OUT_OF_BOUNDS,0);

		drawStriker(strikerx,0);
		//setTimer();

		
		//Initialization for each level
		while(level <= MAX_LEVEL && lives > 0){
			LEDSetString("New level      ");
			setLedMode(2);
			//LEDLoadBuffer();
		 
			lives = NUMBER_OF_BALLS;
			waitStart = 1;
			ball.powerActivated = 0;
			
			drawChar(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y), checkBall(&ball,box,strikerx));
			setBallOverStriker(&ball, strikerx);
			drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
			
			createBoxes(box,level);
			for(i = 0; i < box->size; i++){
				drawBox(box->x[i],box->y[i],box->durability[i]);   
			}
			gotoxy(R_EDGE_COORD + 5, 14);
			printf("-Level %d-     ", level);
			gotoxy(R_EDGE_COORD + 5,15);
			printf("Balls left: %d    ", (lives + 1));
			
			
			
			while(lives > 0 && box->boxesLeft > 0){
						
					
						
						key = getKey();

						if(key == 1){
							if(!waitStart && !pause){
								pause = 1;
							}else if(pause){
								pause = 0;
							}
							waitStart = 0;
						}
						
						if(!pause){
						
							if(key == 2){
								moveStriker(&strikerx, 1);
								moveDrawStriker(strikerx,1);
							}else if(key == 4){
									moveStriker(&strikerx,0);
									moveDrawStriker(strikerx,0);
							 }else if(key == 6){
									if(ball.power >= 500){
										ball.powerActivated = 1;
									}
							 }


							if(getCentis() - 50 > refreshTime){

								if(!waitStart){
									refreshTime = getCentis();
									drawChar(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y), checkBall(&ball,box,strikerx));
									
									if(ball.outOfBounds){
										ball.outOfBounds = 0;
										lives--;
										waitStart = 1;
										ball.power = 0;
										gotoxy(R_EDGE_COORD + 5,15);
										printf("Balls left: %d    ", lives);
										
									}
									moveBall(&ball);
									drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);

								}else{
								drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),7);
								setBallOverStriker(&ball, strikerx);
								drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
								}
								if(ball.powerActivated){
									ball.power--;
									if(ball.power <= 0){
										ball.power = 0;
										ball.powerActivated = 0;
									}
								}
								
							}
						}//!pause
			}//while
			level ++;
		}//while - level
	
	return lives;
}
