#ifndef _REFBALL_H_
#define _REFBALL_H_
#define STRIKER_SPEED 2
#define L_EDGE_COORD 2
#define R_EDGE_COORD 100
#define STRIKER_WIDTH 2
#define OUT_OF_BOUNDS 100
#define GAMESPEED 5
#define OVER_STRIKER 2
#define STRIKER_Y  50
#define STRIKER_START  40
#define TOP_EDGE_COORD 2
  typedef struct{
  long x,y, xdir, ydir;
  unsigned char power;
  } Ball;

  void moveBall(Ball * ball);
  void moveStriker(char * x,direction);
  void checkBall(Ball * ball, unsigned char x);
  long toTerminalCoordinates(long x);

#endif
