#include <eZ8.h>
#include <sio.h>
#include "ansi.h"
#include "menu.h"
#include "graphics.h"



//char selectedOption = 0;

	

void initiateMenu(){
	clrscr();
	fgcolor(6);
	bgcolor(7);
	drawLogo();
	gotoxy(1,11);
	printf("Welcome to ReflexBall\nMove up / down in the menu with the left / middle button.\nSelect with right button.\n\n");

	printf("  1. Start game.\n");
	printf("  2. Change difficulty:\n");
	printf("  3. Show instructions.\n");

	//Prints the menu-select marker
	moveMarker(1);

}

void moveMarker (short selectedOption){
	int i;
	fgcolor(1);
	bgcolor(7);
	//Clears the first column
	for(i = 0;i < 3; i++){
		gotoxy(1,LINE_NUMBER + i);
		printf(" ");
	}
	gotoxy(1, LINE_NUMBER + selectedOption - 1);
	printf("*");
	
}



/*
//Moves the menu-select
void moveMarker(char up){
	int i;
	fgcolor(1);
	bgcolor(7);
	//Clears the first column
	gotoxy(1,LINE_NUMBER + selectedOption - 1);
	printf(" ");
	if(up){
		selectedOption --;
		if(selectedOption == 0){
			selectedOption = 3;
		}
	}else{
		selectedOption ++;
		if(selectedOption == 4){
			selectedOption = 1;
		}
	}
	//Prints marker
	gotoxy(1, LINE_NUMBER + selectedOption - 1);
	printf("*");

}

char getChoice(){
	return selectedOption;
}
*/


		
	
	
	
