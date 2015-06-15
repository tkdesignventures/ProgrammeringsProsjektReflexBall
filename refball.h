#ifndef _refball_h_
#define _ref_ball_h
#define STRIKER_SPEED 2;
#define L_EDGE_COORD 2;
#define R_EDGE_COORD 100;
#define STRIKER_WIDTH 2;
#define STRIKER_SPEED 1;
#define OUT_OF_BOUNDS 100 << 14;
#define GAMESPEED 5; // Frequency/10
#define OVER_STRIKER 2;
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


void moveBall();
void checkBall();
void updateGame();
void moveStriker(unsigned char direction);
void initGame(unsigned char li, unsigned char d, unsigned char lev);
void pause();
unsigned char isDead(););
unsigned char isDone();
void setBall();
void checkBoxes();
void startGame();

#endif
