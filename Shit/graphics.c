#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h>             // special encore serial i/o routines
#include "ansi.h"
#include "graphics.h"


void drawBox(unsigned char x, unsigned char y,unsigned char color, char boxSize){
	char j;
	
	//Avoids the color yellow
	if(color == 3) color = 13;
	
	fgcolor(color);
	drawBounds(x,y,x+(boxSize-1),y+1,color);
	//draws last line
	fgcolor(color);
	gotoxy(x,y+1);
	printf("%c",192);
	for(j=0; j < (boxSize-2); j++){
	printf("%c",196);
	}
	printf("%c",217);
	fgcolor(0);
}
void drawChar(unsigned char x, unsigned char y,char tegn){
	gotoxy(x,y);
	printf("%c",tegn);
}
void drawBall(unsigned char x, unsigned char y, unsigned char color){
	fgcolor(color);
	gotoxy(x,y);
	printf("%c", 111);
	fgcolor(0);
}
void moveDrawStriker(unsigned char x, unsigned char direction, char strikerWidth, char strikerY){
	fgcolor(0);
	if(direction==1){
		gotoxy(x - (strikerWidth +2),strikerY);
		printf("   ");
		gotoxy(x + strikerWidth - 2,strikerY);
		printf("%c%c%c",220,220,220);
	}else{
		gotoxy(x + strikerWidth + 1,strikerY);
		printf("   ");
		gotoxy(x - strikerWidth,strikerY);
		printf("%c%c%c",220,220,220);
	}
}
void drawStriker(unsigned char x, unsigned char color, char strikerWidth, char strikerY){
	unsigned char i;
	fgcolor(color);
	gotoxy(x-strikerWidth,strikerY);
	for(i=0;i < 2*strikerWidth + 1;i++)
		printf("%c",220);
	fgcolor(0);
}
void drawBounds(int x1,int y1, int x2, int y2, unsigned char color){
	int i,j;
	char hs,vs,h1,h2,h3,h4;
	int height = y2 - y1+1;
	int width = x2 - x1+1;
	fgcolor(color);
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
fgcolor(0);
}

void drawLogo(){
	gotoxy(LEFT_BORDER,5);
	printf("||******************************************||\n");
	gotoxy(LEFT_BORDER,6);
	printf(" _____       __ _             ____        _ _ \n");
	gotoxy(LEFT_BORDER,7);
	printf("|  __ \     / _| |           |  _ \      | | |\n");
	gotoxy(LEFT_BORDER,8);
	printf("| |__) |___| |_| | _____  __ | |_) | __ _| | |\n");
	gotoxy(LEFT_BORDER,9);
	printf("|  _  // _ \  _| |/ _ \ \/ / |  _ < / _` | | |\n");
	gotoxy(LEFT_BORDER,10);
	printf("| | \ \  __/ | | |  __/>  <  | |_) | (_| | | |\n");
	gotoxy(LEFT_BORDER,11);
	printf("|_|  \_\___|_| |_|\___/_/\_\ |____/ \__,_|_|_|\n");
	gotoxy(LEFT_BORDER,12);
	printf("||******************************************||\n");
	gotoxy(LEFT_BORDER,13);
	printf("Group 3, s144012, s144045, s144021, June 2015   ");
	//printf("Ver. 0.2.0.3 Beta\n                             ");

}

void drawGameOver(){
	int i;
	clrscr();
	for(i = 0; i < 4; i++){
		gotoxy(LEFT_BORDER,5);
		printf(" .----------------.  .----------------.  .----------------.  .----------------.  \n");
		gotoxy(LEFT_BORDER,6);
		printf("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
		gotoxy(LEFT_BORDER,7);
		printf("| |    ______    | || |      __      | || | ____    ____ | || |  _________   | | \n");
		gotoxy(LEFT_BORDER,8);
		printf("| |  .' ___  |   | || |     /  \     | || ||_   \  /   _|| || | |_   ___  |  | | \n");
		gotoxy(LEFT_BORDER,9);
		printf("| | / .'   \_|   | || |    / /\ \    | || |  |   \/   |  | || |   | |_  \_|  | | \n");
		gotoxy(LEFT_BORDER,10);
		printf("| | | |    ____  | || |   / ____ \   | || |  | |\  /| |  | || |   |  _|  _   | | \n");
		gotoxy(LEFT_BORDER,11);
		printf("| | \ `.___]  _| | || | _/ /    \ \_ | || | _| |_\/_| |_ | || |  _| |___/ |  | |  \n");
		gotoxy(LEFT_BORDER,12);
		printf("| |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |\n");
		gotoxy(LEFT_BORDER,13);
		printf("| |              | || |              | || |              | || |              | | \n");
		gotoxy(LEFT_BORDER,14);
		printf("| '--------------' || '--------------' || '--------------' || '--------------' |  \n");
		gotoxy(LEFT_BORDER,15);
		printf(" '----------------'  '----------------'  '----------------'  '----------------'   \n");
		gotoxy(LEFT_BORDER,16);
		printf("                                                                                  \n");
		gotoxy(LEFT_BORDER,17);
		printf(" .----------------.  .----------------.  .----------------.  .----------------.  \n");
		gotoxy(LEFT_BORDER,18);
		printf("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
		gotoxy(LEFT_BORDER,19);
		printf("| |     ____     | || | ____   ____  | || |  _________   | || |  _______     | |\n");
		gotoxy(LEFT_BORDER,20);
		printf("| |   .'    `.   | || ||_  _| |_  _| | || | |_   ___  |  | || | |_   __ \    | |\n");
		gotoxy(LEFT_BORDER,21);
		printf("| |  /  .--.  \  | || |  \ \   / /   | || |   | |_  \_|  | || |   | |__) |   | |\n");
		gotoxy(LEFT_BORDER,22);
		printf("| |  | |    | |  | || |   \ \ / /    | || |   |  _|  _   | || |   |  __ /    | |\n");
		gotoxy(LEFT_BORDER,23);
		printf("| |  \  `--'  /  | || |    \ ' /     | || |  _| |___/ |  | || |  _| |  \ \_  | |\n");
		gotoxy(LEFT_BORDER,24);
		printf("| |   `.____.'   | || |     \_/      | || | |_________|  | || | |____| |___| | | \n");
		gotoxy(LEFT_BORDER,25);
		printf("| |              | || |              | || |              | || |              | | \n");
		gotoxy(LEFT_BORDER,26);
		printf("| '--------------' || '--------------' || '--------------' || '--------------' |\n");
		gotoxy(LEFT_BORDER,27);
		printf(" '----------------'  '----------------'  '----------------'  '----------------' \n");
	}	
	

	scrollText(28, 100);


	printf("\n");
}

void drawVictory(){
	int i;
	clrscr();
	
	for(i = 0; i < 4; i++){

	
		gotoxy(LEFT_BORDER, 5);
		printf("Victory!!!");
		gotoxy(LEFT_BORDER, 6);
		printf("             `          `.-/---/+yyd:`         ::-:::-.```         `                               ");
		gotoxy(LEFT_BORDER, 7);
		printf("            `         `.-/hNy+ommNNNs     ````oNNddmmNNNmmy+:.`    ``                               ");
		gotoxy(LEFT_BORDER, 8);
		printf("            ` ` `    .-/sdNNo:shmNNdo `      .dydmmNmddNmNNNNy/`    ```.  `...::--..                ");
		gotoxy(LEFT_BORDER, 9);
		printf("           ```     .--/+ymNo``  sm+```      ``/::hNNNNNNNNNNNNd`    .  ` .:--::os/yho/              ");
		gotoxy(LEFT_BORDER, 10);
		printf("           `     `-.-/odNNh` ``````       `` +so+/yNNNNNNNMNNMd`   `     :y:/o/yddmNdN/             ");
		gotoxy(LEFT_BORDER, 11);
		printf("         `    `...-+ymNNN+             ` ``..:-/++dNNNdNNNNNMy   ``      -omhss+:mNNmd`            ");
		gotoxy(LEFT_BORDER, 12);
		printf("            ``.--/ymmNNNN.  `           ``:+::+syhddsddNNMMMMm   `        ---`  `yNshmo            ");
		gotoxy(LEFT_BORDER, 13);
		printf("            ```-:/sdmmNNNhoyooo:           .+//+ohmdysmNNMMNMNN: .               .oo-/dN+           ");
		gotoxy(LEFT_BORDER, 14);
		printf("            `.:oshmmNNNNm+-:/sms` ````   `://oydmmm/omNNNNNNNs.`                `/--:smm-          ");
		gotoxy(LEFT_BORDER, 15);
		printf("             -//+ydmNNNNs/+osymmh:--:+oso+:+yhdmmmo+dNNNNNNN+`                  .:--:odNy          ");
		gotoxy(LEFT_BORDER, 16);
		printf("               /ymddmmmmmyyddmmmmmh-.-/oyhdds++sdNdodNmmddmmmy-.-::::::-`  ....` .:.-:odmN`         ");
		gotoxy(LEFT_BORDER, 17);
		printf("            `  ``/dmmmdss+oydmmmmmm-.-:+ssso++ohdos/+////+++/::::/+oosso+.--:+shho:-:ohmmN.        ");
		gotoxy(LEFT_BORDER, 18);
		printf("           `     `./ymdddddmmmmNNNN/---/+++/::/++:---::/+++///+oyhdmh/----::/+sss+/ohddmNN/         ");
		gotoxy(LEFT_BORDER, 19);
		printf("                    `-+hmNNNNNNNNNNh/:--:::::/::-...-:/oosyyhddmmNNh:::/+osyys+---:+oydNNNs        ");
		gotoxy(LEFT_BORDER, 20);
		printf("                       ../oyyhddmmNms/:----:/-:-...-:+oydmmmmmNNNNNys+/+oooo+:---:/+sydNNNs`        ");
		gotoxy(LEFT_BORDER, 21);
		printf("           `          ``    ```.../moo/:---::::-.-:/oydmNNNNNNNNNNNNNms+/:::--:/osyhhdmmdo.`        ");
		gotoxy(LEFT_BORDER, 22);
		printf("           .`         `            /+so+ooy+:::::ohhdmNNmmNNNNNNNNNNNNmdysssssyyhmNNds/.`  `        ");
		gotoxy(LEFT_BORDER, 23);
		printf("          `` ```     `            ``+oshdh+/::/:+hddddmmNNNNNNNNNNNNNNNyydmmmmmmdyo-`     `        `");
		gotoxy(LEFT_BORDER, 24);
		printf("           `    ``  .              `-oo+//:::--:/++oyhmmmNNNNNNNmmmmmmh.``..--.```                 `");
		gotoxy(LEFT_BORDER, 25);
		printf("           `      `                 `+++oso+/:-.-/shhhdmmmmmmmmmmmmmmy.                         `   ");
		gotoxy(LEFT_BORDER, 26);
		printf("            `                       `-+oyhsss/--/oshdddmddhdmmmmmmds:`                             ");
		gotoxy(LEFT_BORDER, 27);
		printf("           `                        `/oyyoo+o/+shddmmmmmmmmmmmmdo.`                                ");
		gotoxy(LEFT_BORDER, 28);
		printf("            .                       .oyhy+//+oshddmmmmmmmmmmmdo.                                   ");
		gotoxy(LEFT_BORDER, 29);
		printf("             `                       ohho////+oydmmNmmmmmmmms-`                                    ");
		gotoxy(LEFT_BORDER, 30);
		printf("              ``                      /+/:///::/ohmmmmmmmmmh:`                                     `");
		gotoxy(LEFT_BORDER, 31);
		printf("               ` ```                 .+://:::-:+ymmmmmmmmdo.         ```  ```  ```   ``   ``   `````");
		gotoxy(LEFT_BORDER, 32);
		printf("               `    ````             /+//:::-:+hmmmmmmmd+.````  ```                          ````   ");
		gotoxy(LEFT_BORDER, 33);
		printf("               `        ````        -://::::/sdmNNNNNNs.                                   ``       ");
		gotoxy(LEFT_BORDER, 34);
		printf("                            ```    /y/:/+syhdNNNNNNNNy`                                  ``         ");
		gotoxy(LEFT_BORDER, 35);
		printf("                `               ``-mNddmNMMMMMMMMMMMMm.                                 ``          ");
		gotoxy(LEFT_BORDER, 36);
	}
	
	
	
	
	
	
	scrollText(37, 100);
	
	
}

void scrollText(char y, char delay){
		//Makes the Game Over / Victory text stay on the screen for a little while
		
	char i, j;
	for(i = 0; i < delay; i++){
		gotoxy(2,y + i);
		printf("                                                                                                  \n");

	}//for

}

void printExampleBoxes(char x, char y,char boxSize){
	int i;
	for(i = 0; i < 5; i++){
		drawBox(x,y + 3*i,7-(i+1),boxSize);
		printf(" Life: %d", (i+1));
	}
	
}	
	

