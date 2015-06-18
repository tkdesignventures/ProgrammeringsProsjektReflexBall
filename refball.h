#ifndef _REFBALL_H_
#define _REFBALL_H_
#define STRIKER_SPEED 2
#define L_EDGE_COORD 2
#define R_EDGE_COORD 160
#define STRIKER_WIDTH 4
#define OUT_OF_BOUNDS 65
#define GAMESPEED 1
#define OVER_STRIKER 20
#define STRIKER_Y  60
#define STRIKER_START  20
#define TOP_EDGE_COORD 2
  typedef struct{
  long x,y,xdir, ydir;
  unsigned char power;
  } Ball;

  void moveBall(Ball * ball);
  void moveStriker(long * x, char direction);
  void checkBall(Ball * ball, int x);
  long toTerminalCoordinates(long x);
  void setBallOverStriker( Ball * ball,  long st);
#endif
