
char selectedOption = 0;

void initiateMenu(){
	clrscr();
	printf("Welcome to ReflexBall\nMove up / down in the menu with the left / middle button.\nSelect with right button.");
	gotoxy(2,3);
	printf("1. Start game\n");
	printf("2. Change difficulty\n");
	printf("3. Show help\n");

	//Prints the menu-select marker
	moveMarker(0);
	
}

//Moves the menu-select
void moveMarker(char up){
	int i;
	//Clears the first column
	gotoxy(1,3 + selectedOption - 1);
	
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
	
	goto(1, 3 + selectedOption - 1);
	printf("*");
	
}

char getChoice(){
	return selectedOption;
}


