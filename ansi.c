#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "ansi.h"

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color      
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}
void underline(char on){
	int d;
	if (on==1){

		d=4;
   }else{
		d=24;

   }
	printf("%c[%dm", ESC, d);
}
void clrscr(){
	bgcolor(7);
	printf("%c[2J", ESC);
}
void clreol(){
	printf("%c[K",ESC);
}
void gotoxy(int x,int y){
	printf("%c[%d;%dH",ESC,y,x);
}
void blink(char on){
	int d;
	if(on==1)
		d=5;
	else
		d=25;
	
	printf("%c[%dm",ESC,d);
}
void reverse(char on){
	int d;
	if(on==1)
		d=7;
		else
		d=27;
	
	printf("%c[%dm",ESC,d);
}

//Tegner et vindu, style=1 enkel linje, style=2 dobbel linje
void window(int x1,int y1,int x2, int y2,int style,char *s){
	int i,j;
	char hs,vs,h1,h2,h3,h4,headerv,headerh;
	int height = y2 - y1+1;
	int width = x2 - x1+1;
	
	//Velger enkel / dobbel linjebredde
	if (style==1){
		hs=196;
		vs=179;
		h1=218;
		h2=191;
		h3=217;
		h4=192;
		headerv=180;
		headerh=195;
	}else{
		hs=205;
		vs=186;
		h1=201;
		h2=187;
		h3=188;
		h4=200;
		headerv=185;
		headerh=204;
	}
	//Printer øverste linje	
	gotoxy(x1,y1);
	//Første hjørne
	printf("%c%c",h1,headerv);
	reverse(1); 
	//Regner længden på strengen
	for(i=0;i<width;i++){
		if(s[i]=='\0')
	break; 
	}
	printf("%s",s);

	
	for(j=0;j<(width-i-4);j++)
		printf(" ");
	reverse(0);
	printf("%c%c ",headerh,h2);
	//Printer de vertikale linjer
	for(i=1;i<=height-2;i++){
		gotoxy(x1,y1+i);
		printf("%c",vs);
		gotoxy(x2,y1+i);
		printf("%c",vs);
	}
	//Printer bunden 
	gotoxy(x2,y1);
	printf("%c",h4);
	
	for(i=1;i<=width-2;i++)
		printf("%c",hs);


	printf("%c",h3);
}

void drawBox(unsigned char x, unsigned char y,unsigned char color){
fgcolor(color);
drawBounds(x,y,x+3,y+1);
//draws last line
	gotoxy(x,y+1);
	printf("%c%c%c%c",192,196,196,217);
fgcolor(0);		
}
void drawStriker(unsigned char x,unsigned char color){
unsigned char i;
fgcolor(color);
gotoxy(x-2,50);
for(i=0;i<5;i++)
	printf("%c",220);
fgcolor(0);
}
void drawBounds(int x1,int y1, int x2, int y2){
	int i,j;
	char hs,vs,h1,h2,h3,h4;
	int height = y2 - y1+1;
	int width = x2 - x1+1;
	fgcolor(0);
	hs=196;
	vs=179;
	h1=218;
	h2=191;
	h3=217;
	h4=192;
	gotoxy(x1,y1);
	printf("%c",h1);
	
	for(i=1;i<=width-2;i++)
		printf("%c",hs);


	printf("%c",h2);
	for(i=1;i<=height-2;i++){
		gotoxy(x1,y1+i);
		printf("%c",vs);
		gotoxy(x2,y1+i);
		printf("%c",vs);
	}

}

//Flytter skrivehodet
void up(int x){
	printf("%c[%dA",ESC,x);
}
void down(int x){
	printf("%c[%dB",ESC,x);
}
void right(int x){
	printf("%c[%dC",ESC,x);
}
void left(int x){
	printf("%c[%dD",ESC,x);
}
