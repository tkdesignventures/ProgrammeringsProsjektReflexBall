#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#define LEFT_BORDER 10
#define LINE_NUMBER 28


void drawBox(unsigned char x, unsigned char y,unsigned char color);
void drawBall(unsigned char x, unsigned char y, unsigned char color);
void drawChar(unsigned char x, unsigned char y,char tegn);
void drawStriker(unsigned char x,unsigned char color);
void drawBounds(int x1,int y1, int x2, int y2,unsigned char color);
void moveDrawStriker(unsigned char x, unsigned char direction);
void drawLogo();
void drawGameOver();
void drawVictory();
void printDelay(char y, char delay);
void printDifficulty(short diff);
void printHelp();
#endif
