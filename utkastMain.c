

void main(){
	char selectedOption;
	char key;
	short difficulty;
	
	difficulty = 1;
	selectedOption = 1;
	
	initiateMenu();
	
	for(;;){
		key = readKey();
		
		
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
			key = readKey();
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
			printHelp();
		}
		
	
	}
	
	
	
	
	
}