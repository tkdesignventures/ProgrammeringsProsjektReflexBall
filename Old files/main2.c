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
  	  char strikerx;
      char key;
  		init_uart(_UART0,_DEFFREQ,_DEFBAUD);
  		clrscr();
      setTimer();
      //Initialize
      strikerx = 30;
      uselessdelay = 0;
      ball.x = (30 << FIX14_SHIFT);
      ball.y = (12 << FIX14_SHIFT);
      ball.xdir = (0.7 << FIX14_SHIFT);
      ball.ydir = (0.7 << FIX14_SHIFT);
      drawBounds(L_EDGE_COORD,TOP_EDGE_COORD,R_EDGE_COORD,OUT_OF_BOUNDS+5);
        for(;;){
          key = getKey();
    				if(key == 1){}

    				else if(key == 2){
      					moveStriker(&strikerx, 1);
                moveDrawStriker(strikerx,1);
                }
    				else if(key == 4){
      					moveStriker(&strikerx,0);
                moveDrawStriker(strikerx,0);
              }
              if(uselessdelay >10000){
      drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),0);
      moveBall(&ball);
      checkBall(&ball,strikerx);
      drawBall(toTerminalCoordinates(ball.x),toTerminalCoordinates(ball.y),7); 
      uselessdelay = 0;
      }
      uselessdelay++;

    }

}
