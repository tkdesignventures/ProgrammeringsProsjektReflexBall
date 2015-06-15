#ifndef _refball_h_
#define _ref_ball_h
#define STRIKER_SPEED 2;
#define L_EDGE_COORD 2;
#define R_EDGE_COORD 100;
#define STRIKER_WIDTH 2;
#define STRIKER_SPEED 1;
#define OUT_OF_BOUNDS 100;
#define GAMESPEED 5; // Frequency/10
#define OVER_STRIKER 2;
#define STRIKER_Y = 50;
#define STRIKER_START = 40;
struct Box {
unsigned char x,y,durability,powertime;
}
struct Ball {
long x,y;
unsigned char power;
long xdir, ydir;
}
struct Striker {
unsigned char x;
}


void moveBall(struct Ball * ball);
void moveStriker(struct Striker * striker,unsigned char direction);
unsigned char checkBall(struct Ball * ball, struct Striker * striker,  struct Box * box, int size);
void checkBoxes(struct Ball * ball, struct Box * box, int size);
unsigned char initGame(struct Ball * ball, struct Striker * striker,  struct Box * box, unsigned char level);
unsigned char toTerminalCoords(long input);
void setBallOverStriker(struct Ball * ball, struct Striker * striker);
unsigned char createBoxes(struct Box * box,char level);

#endif
