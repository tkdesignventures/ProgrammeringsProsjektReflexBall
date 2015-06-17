#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

void drawBox(unsigned char x, unsigned char y,unsigned char color);
void drawBall(unsigned char x, unsigned char y, unsigned char color);
void drawStriker(unsigned char x,unsigned char color);
void drawBounds(int x1,int y1, int x2, int y2);
void moveDrawStriker(unsigned char x, unsigned char direction);

#endif
