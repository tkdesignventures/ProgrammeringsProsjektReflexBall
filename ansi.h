#ifndef _ANSI_H_
#define _ANSI_H_
#define ESC 0x1B

void fgcolor(int foreground);

void bgcolor(int background);

void color(int foreground, int background) ;
void underline(char on);
void clrscr();
void clreol();
void gotoxy(int x,int y);
void blink(char on);
void reverse(char on);
void window(int x1,int y1,int x2, int y2,int style,char *s);
void up(int x);
void down(int x);
void right(int x);
void left(int x);

#endif
