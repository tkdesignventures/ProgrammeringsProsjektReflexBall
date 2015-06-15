#include <eZ8.h>
#include <sio.h>
#include "ansi.h"
#include "menu.h"



char selectedOption = 0;

void printLogo(){
	
	printf("||******************************************||\n");

	printf(" _____       __ _             ____        _ _ \n");
	printf("|  __ \     / _| |           |  _ \      | | |\n");
	printf("| |__) |___| |_| | _____  __ | |_) | __ _| | |\n");
	printf("|  _  // _ \  _| |/ _ \ \/ / |  _ < / _` | | |\n");
	printf("| | \ \  __/ | | |  __/>  <  | |_) | (_| | | |\n");
	printf("|_|  \_\___|_| |_|\___/_/\_\ |____/ \__,_|_|_|\n");

	printf("||******************************************||\n");

	//printf("Ver. 0.2.0.3 Beta\n                             ");
	
}	

void initiateMenu(){
	clrscr();
	fgcolor(6);
	bgcolor(7);
	printLogo();
	gotoxy(1,11);
	printf("Welcome to ReflexBall\nMove up / down in the menu with the left / middle button.\nSelect with right button.\n\n");

	printf("  1. Start game.\n");
	printf("  2. Change difficulty:\n");
	printf("  3. Show help\n");

	//Prints the menu-select marker
	moveMarker(0);

}

//Moves the menu-select
void moveMarker(char up){
	int i;
	
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

void printDifficulty(short diff){
	
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
	
	
	
