#include <eZ8.h>             // special encore constants, macros and flash routines
#include <sio.h> 
#include "keys.h"
#include "ctimer.h"

void iniKeys(){
// sætter datadirektion for keys
PFDD = 0xC0;
PDDD = 0x03;
}
char readKey(){
	char a,b=0;
	a = PFIN;
	if((a & 0x80) == 0) b = 1;
	if((a & 0x40) == 0) b += 2;
	a = PDIN;
	if((a & 0x08) == 0) b += 4;
	return b;
	}
char getKey(){
	char key;
	key=readKey();
	setDelay(5);
	while(getDelay()>0){
	}
	return key &=readKey();

}
