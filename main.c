#include <eZ8.h>             // special encore constants, macros and flash routines
#include "refball.h"
#include "graphics.h"
#include "ctimer.h"
#include "keys.h"
#include <sio.h>
#include "ansi.h"
#include "math.h"
  void main(){
      long uselessdelay;
  		Ball ball;
      Bresenham b;
  	  char strikerx;
	  char key;
	  unsigned long refreshTime;
  		init_uart(_UART0,_DEFFREQ,_DEFBAUD);
  		clrscr();
      //Initialize
      strikerx = 30;
      refreshTime = 100;
      ball.x = (30 << FIX14_SHIFT);
      ball.y = (12 << FIX14_SHIFT);

      ball.xdir = (11 << (FIX14_SHIFT - 4));
      ball.ydir = (-11 << FIX14_SHIFT - 4);
      initLine(&ball,&b);
      drawBounds(L_EDGE_COORD,TOP_EDGE_COORD,R_EDGE_COORD,OUT_OF_BOUNDS);
	    drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);

    	gotoxy(10,10);
		printf("LOOSE");
		setTimer();
        for(;;){
          key = getKey();
    				if(key == 1){
					gotoxy(10,10);
					printf("hey!");
					}

    				else if(key == 2){
      					moveStriker(&strikerx, 1);
	                	moveDrawStriker(strikerx,1);
	                }else if(key == 4){
	      					moveStriker(&strikerx,0);
	                		moveDrawStriker(strikerx,0);
	                 }
            	if(getCentis()- GAMESPEED > refreshTime){
					refreshTime = getCentis();
			  	  	drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),7);
				  	computeNextPixel(&ball,&b);
				  	drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
			      	checkBall(&ball,strikerx,&b);

    		  }


    }

}
