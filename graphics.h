#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#define LINE_NUMBER 15

void drawBox(unsigned char x, unsigned char y,unsigned char color);
void drawBall(unsigned char x, unsigned char y, unsigned char color);
void fixBall(unsigned char x, unsigned char y,char tegn);
void drawStriker(unsigned char x,unsigned char color);
void drawBounds(int x1,int y1, int x2, int y2);
void moveDrawStriker(unsigned char x, unsigned char direction);
void drawLogo();
void drawGameOver();
void printDifficulty(short diff);
#endif
