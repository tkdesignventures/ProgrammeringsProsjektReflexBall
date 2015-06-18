#ifndef _REFBALL_H_
#define _REFBALL_H_
#define STRIKER_SPEED 2
#define L_EDGE_COORD 2
#define R_EDGE_COORD 120
#define STRIKER_WIDTH 4
#define OUT_OF_BOUNDS 65
#define GAMESPEED 1
#define OVER_STRIKER 20
#define STRIKER_Y  60
#define STRIKER_START  20
#define TOP_EDGE_COORD 2
#define BLANK 0
#define EDGE 180
#define TOP 196
#define STRIKER 220
  typedef struct{
  long x,y,xdir, ydir;
  unsigned char power, outOfBounds;
  } Ball;
  typedef struct{
    unsigned char *x, *y, * durability;
    unsigned char size, capacity;
  } Box;

  void moveBall(Ball * ball);
  unsigned char moveStriker(long * x, char direction);
  void checkBall(Ball * ball, int x);
  long toTerminalCoordinates(long x);
  void setBallOverStriker( Ball * ball,  long st);
#endif
