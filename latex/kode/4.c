#include <eZ8.h>
#include <sio.h>
#include "ansi.h"




char readKey(){
char a,b=0;
PEDD = 0xFF;
PGDD = 0xFF;
	a = PFIN; //S�tter a lig inputtet fra knapperne
	//Adderer den v�rdi som knapperne repr�senterer i bin�r format. 
	if((a & 0x80) == 0) b = 1; 
	if((a & 0x40) == 0) b += 2;
	a = PDIN;
	if((a & 0x08) == 0) b += 4;
	return b;
}
//Indl�ser en valgt v�rdi til LED
void writeLed(unsigned char i){
PEDD = 0x00;
PGDD = 0x00;
PEOUT = 0x0F;
PGOUT = i & 0x7F;
PEOUT |= 0x80;

}
void main(){
	char temp,key;
	int i=0;
	init_uart(_UART0,_DEFFREQ,_DEFBAUD);

	while(1!=2){
		key=readKey();
		if(key != temp){
			temp=key;
			//T�ller op, hver gang der er en �ndring p� keys, som ikke er, at den �ndre sig til nul.
			if(key != 0x00){
				i += 1;
				clrscr();
				printf("%d",i);
			}
		}
	writeLed(i);							
	}

}
	
