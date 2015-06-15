#ifndef _refball_h_
#define _ref_ball_h
#define STRIKER_SPEED 2;
#define L_EDGE_COORD 2;
#define R_EDGE_COORD 100;
#define STRIKER_WIDTH 2;
#define OUT_OF_BOUNDS 100;
#define GAMESPEED 5; // Frequency/10
#define OVER_STRIKER 2;
#define STRIKER_Y = 50;
#define STRIKER_START = 40;
typedef struct {
unsigned char * x,y,durability,powertime;
unsigned char capacity,size;
} Box;
typedef struct{
long x,y;
unsigned char power;
long xdir, ydir;
} Ball;
typedef struct {
unsigned char x;
} Striker ;

Box * newBoxStack(void);
void moveBall( Ball * ball);
void moveStriker( Striker * striker,unsigned char direction);
unsigned char checkBall( Ball * ball,  Striker * striker,   Box * box);
void checkBoxes( Ball * ball,  Box * box);
void initGame( Ball * ball,  Striker * striker,   Box * box, unsigned char level);
unsigned char toTerminalCoords(long input);
void setBallOverStriker( Ball * ball,  Striker * striker);
void createBoxes( Box * box,char level);

#endif
