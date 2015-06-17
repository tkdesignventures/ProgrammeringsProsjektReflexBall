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
  	  char strikerx;
	    char key;
		char waitStart;
	    unsigned long refreshTime;
  		init_uart(_UART0,_DEFFREQ,_DEFBAUD);
  		clrscr();
      //Initialize
      strikerx = 30;
      refreshTime = 100;
      ball.x = 30 << FIX14_SHIFT;
      ball.y = 12 << FIX14_SHIFT;
	  waitStart = 1;

      ball.xdir = (-11 << (FIX14_SHIFT - 4));
      ball.ydir = (-11 << (FIX14_SHIFT - 4));

	  //setBallOverStriker(&ball, strikerx);
	  gotoxy(15,15);
	  
	  
	  
      drawBounds(L_EDGE_COORD,TOP_EDGE_COORD,R_EDGE_COORD,OUT_OF_BOUNDS);
	    drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
		drawStriker(strikerx,0);


		    setTimer();



        for(;;){
          gotoxy(20,20);
         

          			key = getKey();
    				if(key == 1){
					gotoxy(10,10);
					printf("Rotate");
					rotate(&ball, 20);
					waitStart = 0;
					}

    				else if(key == 2){
      					moveStriker(&strikerx, 1);
	                	moveDrawStriker(strikerx,1);
	                }else if(key == 4){
	      					moveStriker(&strikerx,0);
	                		moveDrawStriker(strikerx,0);
	                 }
				
				if(!waitStart){
				
					if(getCentis()- GAMESPEED > refreshTime){

							  refreshTime = getCentis();
							  drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),7);
							moveBall(&ball);
							drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
						  checkBall(&ball,strikerx);


				  }
				}else{
					ball.x = strikerx;
					ball.y = STRIKER_Y + OVER_STRIKER;
				}
    }
	

}

//Spørsmål til i morgen:
//0. Hvorfor kan bolden køre gjennem strikeren
//1. Hvorfor flytter ikke bolden sig
//2. Hvorfor fungerer ikke setBallOverStriker()

