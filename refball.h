#ifndef _REFBALL_H_
#define _REFBALL_H_
#define STRIKER_SPEED 2
#define L_EDGE_COORD 2
#define R_EDGE_COORD 80
#define STRIKER_WIDTH 4
#define OUT_OF_BOUNDS 45
#define GAMESPEED 1
#define OVER_STRIKER 20
#define STRIKER_Y  45
#define STRIKER_START  20
#define TOP_EDGE_COORD 2
  typedef struct{
  int x,y;
  long xold,yold, xdir, ydir;
  unsigned char power;
  } Ball;
  typedef struct{
   int numerator, shortest, longest,dx1,dx2,dy1,dy2;
  } Bresenham;
  typedef struct {
  	unsigned char x,y;
  } TVector ;

  void moveBall(Ball * ball);
  void moveStriker(char * x, char direction);
  void checkBall(Ball * ball, unsigned char x,Bresenham * b, TVector * nextPos);
  long toTerminalCoordinates(long x);

  void initLine(Ball * ball, Bresenham * b);
  void computeNextPixel(Ball * ball, Bresenham * b, TVector * vector);
#endif
