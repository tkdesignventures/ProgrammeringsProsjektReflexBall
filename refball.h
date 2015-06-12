#ifndef _refball_h_
#define _ref_ball_h
#define STRIKER_SPEED 2;
#define L_EDGE 0;
#define R_EDGE 1;
#define BOX_EDGE 2;
#define STRIKER_EDGE 3;
#define L_EDGE_COORD 2;
#define R_EDGE_COORD 100;
#define STRIKER_WIDTH 2;
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
unsigned char lastx;
}


void moveBall();
void checkBall();
void updateGame();
void moveStriker(unsigned char direction);
void initGame(unsigned char lives, unsigned char diff, unsigned char level);
void pause();
unsigned char isDead();
void newDir(long x, long y, unsigned char type);
unsigned char isDone();
void setBall();


#endif
