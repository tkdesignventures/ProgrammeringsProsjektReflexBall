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
#include <string.h>

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
	
	//iniKeys();
	LEDInit();
	LEDSetString("Welcome    ");
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
			if(victory >= 0){
				LEDSetString("Victory    ");
				setLedMode(2);
				drawVictory();
			}else{
				drawGameOver();
				LEDSetString("Game over. Try again.    ");
				setLedMode(2);
			}
			
			initiateMenu();
			printDifficulty(difficulty);
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
		
		int i, livesPerLevel;

  	  	Ball ball;
		Box * box = newBoxStack();
  	  	long strikerx;
		char key, lives, level, pause;
		char waitStart, gameDelay;
  	    unsigned long refreshTime;
    	char str[40];
		char temp[3];
		
    	clrscr();

		  //Initialize
		  level = 1;
		  lives = 0;
		  strikerx = 30;
		  refreshTime = 100;
		  ball.x = 5 << FIX14_SHIFT;
		  ball.y = 5 << FIX14_SHIFT;
		  ball.outOfBounds = 0;
		  ball.power = 0;
		  pause = 0;
		  
		  temp[2] = '\0';
		
		if(difficulty == 1){
			livesPerLevel = 9;
			gameDelay = 50;
		}else if(difficulty == 2){
			livesPerLevel = 5;
			gameDelay = 35;
		}else{
			livesPerLevel = 3;
			gameDelay = 20;
		}
		 
		  
		drawBounds(L_EDGE_COORD,TOP_EDGE_COORD,R_EDGE_COORD,OUT_OF_BOUNDS,0);

		drawStriker(strikerx,0,STRIKER_WIDTH, STRIKER_Y);
		
		

		
		//Initialization for each level
		while(level <= MAX_LEVEL && lives >= 0){
			
		 
			lives = livesPerLevel;
			waitStart = 1;
			ball.powerActivated = 0;
			ball.power = 0;
			
			//Sends info to LED display
			temp[1]=(char)(CHARSET_START + level);
			temp[0] = ' ';
			str[0] = '\0';
			strcat(str, "Level");
			strcat(str, temp);
			temp[1] = (char)(CHARSET_START + lives);
			strcat(str,"    ");
			strcat(str,temp);
			temp[1] = (char)(CHARSET_START + ball.power);
			strcat(str, temp);
			LEDSetString(str);
			setLedMode(2);
			
			drawChar(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y), checkBall(&ball,box,strikerx));
			setBallOverStriker(&ball, strikerx);
			drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
			
			createBoxes(box,level);
			for(i = 0; i < box->size; i++){
				drawBox(box->x[i],box->y[i],7 - box->durability[i]);   
			}
			
			
			
			
			while(lives >= 0 && box->boxesLeft > 0){
												
						key = getKey();

						if(key == 1){
							/*if(!waitStart && !pause){
								pause = 1;
							}else if(pause){
								pause = 0;
							}*/
							waitStart = 0;
						}
						
						if(!pause){
						
							if(key == 2){
								moveStriker(&strikerx, 1);
								moveDrawStriker(strikerx,1,STRIKER_WIDTH,STRIKER_Y);
							}else if(key == 4){
									moveStriker(&strikerx,0);
									moveDrawStriker(strikerx,0,STRIKER_WIDTH,STRIKER_Y);
							 }else if(key == 6){
									if(ball.power >= POWER_LIMIT){
										ball.powerActivated = 1;
										str[0] = '\0';
										strcat(str,"Power!");
										temp[1] = (char)(lives + CHARSET_START);
										strcat(str,temp);
										temp[1] = (char)(ball.power + CHARSET_START);
										strcat(str,temp);
										strcat(str," ");
										LEDSetString(str);
										setLedMode(2);
										printf('\0007');
									}
							 }else if(key == 7){
								 pause = 1;
								 clrscr();
							 }


							if(getCentis() - gameDelay > refreshTime){

								if(!waitStart){
									refreshTime = getCentis();
									drawChar(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y), checkBall(&ball,box,strikerx));
									
									if(ball.outOfBounds){
										ball.outOfBounds = 0;
										lives--;
										waitStart = 1;
										ball.power = 0;
										ball.powerActivated = 0;							
									}
									
									if(!ball.powerActivated || ball.power < POWER_LIMIT){
										str[0] = '\0';
										temp[1] = (char)(CHARSET_START + lives);
										strcat(str,temp);
										temp[1] = (char)(CHARSET_START + ball.power);
										strcat(str,temp);
										strcat(str," ");
										setLedMode(3);
										LEDSetString(str);										
										LEDLoadBuffer();
									}
									moveBall(&ball);
									drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),ball.powerActivated);

								}else{
								drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),7);
								setBallOverStriker(&ball, strikerx);
								drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
								}
								
								
							}
						}//!pause
			}//while
			level ++;
		}//while - level
	
	return lives;
}
