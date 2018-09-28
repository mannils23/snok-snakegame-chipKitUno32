#include <stdint.h>
#include <pic32mx.h>
#include "snokheader.h"

void resetSettings(){
	setGameSpeed(getStandardGameSpeed());
	setSnokLength(getStandardSnokLength());
	resetTailLengthIndex();
	resetHead();
	return;
}

void resetTail(){
	resetStoreTailIndex();
	resetRemoveTailIndex();
	resetTailLengthIndex();
	resetCurrentTailLength();
	return;
}

void resetApple(){
	darkApple();
	turnOffApple();
	return;
}

void resetGameBackdrop(){
	int i;
	for(i = 0; i < 128; i++){
		gameBackdrop[0*128 + i] = 1;
		gameBackdrop[1*128 + i] = 0;
		gameBackdrop[2*128 + i] = 0;
		gameBackdrop[3*128 + i] = 128;

	}
	for(i = 0; i < 4; i++){
		gameBackdrop[i*128] = 255;
		gameBackdrop[i*128 + 127] = 255;
	}
	return;
}