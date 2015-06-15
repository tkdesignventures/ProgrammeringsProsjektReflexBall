void main(){
struct Box box[];
struct Ball ball ;
struct Striker striker;
unsigned char gameActive;
unsigned char lives;
unsigned long gameTime;
unsigned char boxesLeft;
unsigned char waitStart; // Waits for user input to start the game. The ball is placed over the striker when it's true
unsigned long refreshTime;
}
void initGame(unsigned char l, unsigned char diff, unsigned char lev){
	//Initialiserer nogle variable
	gameTime = 0;
	refreshTime=0;
	gameActive = 1;
	boxesLeft = 0;
	lives = l;
	striker.x = STRIKER_START;
	setBallOverStriker();
	createBoxes(lev);
	//drawBackground;
	drawBounds(L_EDGE_COORD,TOP_EDGE_COORD, R_EDGE_COORD, TOP_EDGE_COORD)
	drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
	drawStriker(striker.x,0);
  }

	long updateGame() {
		if(getCentis()- GAMESPEED >= refreshTime )
		{
			refreshTime = getCentis();
			if(gameActive){
				gameTime += GAMESPEED;
					if(!waitStart){
							drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),7);
							moveBall();
							drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
							checkBall();
							}
					else {
							drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),7);
							setBallOverStriker();
							drawBall(toTerminalCoords(ball.x),toTerminalCoords(ball.y),0);
							}
					}
					return
	}
