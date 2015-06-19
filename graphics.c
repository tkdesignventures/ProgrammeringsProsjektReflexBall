#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "ansi.h"
#include "graphics.h"
#include "refball.h"

void drawBox(unsigned char x, unsigned char y,unsigned char color){
	char j;
	fgcolor(color);
	drawBounds(x,y,x+(BOXSIZE-1),y+1);
	//draws last line
	gotoxy(x,y+1);
	printf("%c",192);
	for(j=0; j < (BOXSIZE-2); j++){
	printf("%c",196);
	}
	printf("%c",217);
	fgcolor(0);
}
void fixBall(unsigned char x, unsigned char y,char tegn){
	gotoxy(x,y);
	printf("%c",tegn);
}
void drawBall(unsigned char x, unsigned char y, unsigned char color){
	fgcolor(color);
	gotoxy(x,y);
	printf("%c", 111);
	fgcolor(0);
}
void moveDrawStriker(unsigned char x, unsigned char direction){
	fgcolor(0);
	if(direction==1){
		gotoxy(x-3,STRIKER_Y);
		printf(" ");
		gotoxy(x+2,STRIKER_Y);
		printf("%c",220);
	}else{
		gotoxy(x+3,STRIKER_Y);
		printf(" ");
		gotoxy(x-2,STRIKER_Y);
		printf("%c",220);
	}
}
void drawStriker(unsigned char x, unsigned char color){
	unsigned char i;
	fgcolor(color);
	gotoxy(x-2,STRIKER_Y);
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

	for(i=1;i<=width-2;i++){
		printf("%c",hs);
	}

	printf("%c",h2);

	for(i=1;i<=height-2;i++){
		gotoxy(x1,y1+i);
		printf("%c",vs);
		gotoxy(x2,y1+i);
		printf("%c",vs);
	}

}

void drawLogo(){
	gotoxy(2,2);
	printf("||******************************************||\n");

	printf(" _____       __ _             ____        _ _ \n");
	printf("|  __ \     / _| |           |  _ \      | | |\n");
	printf("| |__) |___| |_| | _____  __ | |_) | __ _| | |\n");
	printf("|  _  // _ \  _| |/ _ \ \/ / |  _ < / _` | | |\n");
	printf("| | \ \  __/ | | |  __/>  <  | |_) | (_| | | |\n");
	printf("|_|  \_\___|_| |_|\___/_/\_\ |____/ \__,_|_|_|\n");

	printf("||******************************************||\n");

	printf("Group 3, s144012, s144045, s144021, June 2015   ");
	//printf("Ver. 0.2.0.3 Beta\n                             ");

}

void drawGameOver(){
	int i;
	
	gotoxy(10,5);
	printf(" .----------------.  .----------------.  .----------------.  .----------------.  \n");
	gotoxy(10,6);
	printf("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
	gotoxy(10,7);
	printf("| |    ______    | || |      __      | || | ____    ____ | || |  _________   | | \n");
	gotoxy(10,8);
	printf("| |  .' ___  |   | || |     /  \     | || ||_   \  /   _|| || | |_   ___  |  | | \n");
	gotoxy(10,9);
	printf("| | / .'   \_|   | || |    / /\ \    | || |  |   \/   |  | || |   | |_  \_|  | | \n");
	gotoxy(10,10);
	printf("| | | |    ____  | || |   / ____ \   | || |  | |\  /| |  | || |   |  _|  _   | | \n");
	gotoxy(10,11);
	printf("| | \ `.___]  _| | || | _/ /    \ \_ | || | _| |_\/_| |_ | || |  _| |___/ |  | |  \n");
	gotoxy(10,12);
	printf("| |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |\n");
	gotoxy(10,13);
	printf("| |              | || |              | || |              | || |              | | \n");
	gotoxy(10,14);
	printf("| '--------------' || '--------------' || '--------------' || '--------------' |  \n");
	gotoxy(10,15);
	printf(" '----------------'  '----------------'  '----------------'  '----------------'   \n");
	gotoxy(10,16);
	printf("                                                                                  \n");
	gotoxy(10,17);
	printf(" .----------------.  .----------------.  .----------------.  .----------------.  \n");
	gotoxy(10,18);
	printf("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
	gotoxy(10,19);
	printf("| |     ____     | || | ____   ____  | || |  _________   | || |  _______     | |\n");
	gotoxy(10,20);
	printf("| |   .'    `.   | || ||_  _| |_  _| | || | |_   ___  |  | || | |_   __ \    | |\n");
	gotoxy(10,21);
	printf("| |  /  .--.  \  | || |  \ \   / /   | || |   | |_  \_|  | || |   | |__) |   | |\n");
	gotoxy(10,22);
	printf("| |  | |    | |  | || |   \ \ / /    | || |   |  _|  _   | || |   |  __ /    | |\n");
	gotoxy(10,23);
	printf("| |  \  `--'  /  | || |    \ ' /     | || |  _| |___/ |  | || |  _| |  \ \_  | |\n");
	gotoxy(10,24);
	printf("| |   `.____.'   | || |     \_/      | || | |_________|  | || | |____| |___| | | \n");
	gotoxy(10,25);
	printf("| |              | || |              | || |              | || |              | | \n");
	gotoxy(10,26);
	printf("| '--------------' || '--------------' || '--------------' || '--------------' |\n");
	gotoxy(10,27);
	printf(" '----------------'  '----------------'  '----------------'  '----------------' \n");
	//Makes the Game Over text stay on the screen for a little while
	
	for(i = 0; i < 2; i++){
		gotoxy(10,28);
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		printf("                                                                                                  \n");
		
	}//for


	printf("\n");
}

void printDifficulty(short diff){
	fgcolor(1);
	bgcolor(7);

	gotoxy(25,LINE_NUMBER + 1);

	if(diff == 1){
		printf(" [Easy]   ");
	}else if(diff == 2){
		printf(" [Medium] ");
	}else if(diff == 3){
		printf(" [Hard]   ");
	}else{
		printf(" [Error]  ");
	}
}

void printHelp(){
	gotoxy(5,35);
	printf("Instructions\n");
	printf("Use the left and middle button on the board to control the striker.\n");
	printf("Hit the right button to start or to reset the ball.");
	printf("Your mission is to stay alive and eliminate all the boxes.\n");
	printf("If you loose the ball you will loose a life.\n");
	printf("Watch out for power-ups!\n");

}

