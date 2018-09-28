#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "snokheader.h"  /* Declatations for these labs */

void checkBtns(void);
int pressed = 0;
int randomNumber = 0;
int switched = 0;

void game(){
	checkBtns();
	
	if(timeoutCount >= getGameSpeed()){
		timeoutCount = 0;
		checkSwitches();
		if(!appleExists()){
		spawnApple();
		}
		nextFrame();	
		display_image(0, gameBackdrop);
	}
	if(randomNumber > 10000){
		randomNumber = 0;
	}
}


// Checks button registers and sends values to turn function while in game
void checkBtns(){										
	if((getBtns() & 10) && pressed == 0){
		pressed = 1;
		turn((getBtns() & 10));
	}
	else if((getBtns() & 10) == 0){
		buttonDelay++;
		if(buttonDelay > 13000){
		buttonDelay = 0;
		pressed = 0;	
		}
	}
	if(getBtns() & 1){
		die();
		menu();
	}
	return;
}

void checkSwitches(){
	if(getSwitches() & 1 && switched == 0){
		switched = 1;
		int delayer = 0;
		display_image(0, lightSpeed);
		setGameSpeed(100);
		while(1){
			if (timeoutCount > 10000){
				PORTE += 25;
				timeoutCount = 0;
				delayer++;
				if(delayer > 10){
					PORTE = 0;
					return;
				}
			}

		}
	}
	else if( !(getSwitches() & 1) ){
		switched = 0;
	}
}



















