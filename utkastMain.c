

void main(){
	char selectedOption;
	char key;
	short difficulty;
	
	selectedOption = 1;
	
	initiateMenu();
	
	for(;;){
		key = readKey();
		short difficulty = 2;
		
		//Navigates the menu
		while(key != KEY_RIGHT){
			//Move up
			if(key == KEY_MIDDLE){
				selectedOption++;
				if(selectedOption == 4){
					selectedOption == 1;
				}
				moveMarker(selectedOption);
			//Move down
			}else if(key == KEY_LEFT){
				selectedOption--;
				if(selectedOption == 0){
					selectedOption == 3;
				}
				moveMarker(selectedOption);
			}
		}
		
		if(selectedOption == 1){
			Game(difficulty);
		}else if(selectedOption == 2){
			difficulty ++;
			if(difficulty == 4){
				difficulty = 1;
			}
			printDifficulty(difficulty);
		}
		else if(selectedOption == 3){
			gotoxy(5,35);
			printf("Instructions\n");
			printf("Use the left and middle button on the board to control the striker.\n");
			printf("Hit the right button to start / pause the game");
			printf("Your mission is to stay alive and eliminate all the boxes with the ball.\n");
			printf("If you loose the ball you will loose a life.\n");
			printf("Watch out for power-ups!\n");
			
		}
		
	
	}
	
	
	
	
	
}