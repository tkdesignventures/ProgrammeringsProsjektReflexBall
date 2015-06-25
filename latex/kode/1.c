#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines

#define ESC 0x1B

void fgcolor(int foreground) {
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
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
//Tænder/slukker for understregning
void underline(char on){
	int d;
	if (on==1){

		d=4;
   }else{
		d=24;

   }
	printf("%c[%dm", ESC, d);
}
//Renser skærmen
void clrscr(){
	bgcolor(7);
	printf("%c[2J", ESC);
}
//Renser resten af linjen 
void clreol(){
	printf("%c[K",ESC);
}
//Flytter markøren til x,y
void gotoxy(int x,int y){
	printf("%c[%d;%dH",ESC,x,y);
}
//Bruges til attænde/slukke for funktionen blink
void blink(char on){  
	int d;
	if(on==1)
		d=5;
	else
		d=25;
	
	printf("%c[%dm",ESC,d);
}
//Bruges til at tænde/slukke reverse funktionen
void reverse(char on){  
	int d;
	if(on==1)
		d=7;
		else
		d=27;
	
	printf("%c[%dm",ESC,d);
}

//Tegner et vindue, style=1 enkel linje, style=2 dobbel linje
void window(int x1,int y1,int x2, int y2,int style,char *s){
	int i,j;
	char hs,vs,h1,h2,h3,h4,headerv,headerh;
	int height = x2 - x1+1;
	int width = y2 - y1+1;
	
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
		gotoxy(x1+i,y1);
		printf("%c",vs);
		gotoxy(x1+i,y2);
		printf("%c",vs);
	}
	//Printer bunden 
	gotoxy(x2,y1);
	printf("%c",h4);
	
	for(i=1;i<=width-2;i++)
		printf("%c",hs);


	printf("%c",h3);
}

//Flytter skrivehodet
void up(x){
	printf("%c[%dA",ESC,x);
}
void down(x){
	printf("%c[%dB",ESC,x);
}
void right(x){
	printf("%c[%dC",ESC,x);
}
void left(x){
	printf("%c[%dD",ESC,x);
}

//Bruges til at teste funktionen
void main() {
init_uart (_UART0,_DEFFREQ, _DEFBAUD);
clrscr();
underline(0);
gotoxy(10,10);
printf("HEJ!!!!!!! \n hej \n \n tore");
window(6,9,25,25,2,"hello freinds");
do {} while (1!=2);
}
