#include <stdint.h>
#include <pic32mx.h>
#include "snokheader.h"

int xDir = 1;
int yDir = 0;
unsigned int x[] = {4,4,3,3};
unsigned int y[] = {6,7,6,7};
int tailCoords[200][2][2];
int tailLengthIndex = 5;
int storeTailIndex = 0;
int removeTailIndex = 0;
int currentTailLength = 0;
int hasSlithered = 0;

void moveY(){							// ORDNINGEN ÄR VIKTIG, GÅR INTE MED LOOP, ÄNDRA EJ
	if(yDir > 0){
		dark(x[1], y[1]);
		addDirToCoordinates(1);
		dark(x[3], y[3]);
		addDirToCoordinates(3);

		storeTailCoords(x[0], y[0], x[2], y[2]);
		incrementStoreTailIndex();

		addDirToCoordinates(0);
		addDirToCoordinates(2);
	}
	else if(yDir < 0){
		dark(x[0], y[0]);
		addDirToCoordinates(0);
		dark(x[2], y[2]);
		addDirToCoordinates(2);

		storeTailCoords(x[1], y[1], x[3], y[3]);
		incrementStoreTailIndex();

		addDirToCoordinates(1);
		addDirToCoordinates(3);
	}
	return;
}

void moveX(){							// ORDNINGEN ÄR VIKTIG, GÅR INTE MED LOOP, ÄNDRA EJ	
	if(xDir > 0){
		dark(x[0], y[0]);
		addDirToCoordinates(0);
		dark(x[1], y[1]);
		addDirToCoordinates(1);

		storeTailCoords(x[2], y[2], x[3], y[3]);
		incrementStoreTailIndex();

		addDirToCoordinates(2);
		addDirToCoordinates(3);
	}
	else if(xDir < 0){
		dark(x[2], y[2]);
		addDirToCoordinates(2);
		dark(x[3], y[3]);
		addDirToCoordinates(3);

		storeTailCoords(x[0], y[0], x[1], y[1]);
		incrementStoreTailIndex();

		addDirToCoordinates(0);
		addDirToCoordinates(1);
	}
	return;
}

void storeTailCoords(firstx, firsty, secx, secy){
	tailCoords[storeTailIndex][0][0] = firstx;
	tailCoords[storeTailIndex][0][1] = firsty;
	tailCoords[storeTailIndex][1][0] = secx;
	tailCoords[storeTailIndex][1][1] = secy;
}

void shiftTailCoordsRight(){
	int i;
	for(i = tailLengthIndex; i > removeTailIndex - 2; i--){
	tailCoords[i + 2][0][0] = tailCoords[i + 1][0][0];
	tailCoords[i + 2][0][1] = tailCoords[i + 1][0][1];
	tailCoords[i + 2][1][0] = tailCoords[i + 1][1][0];
	tailCoords[i + 2][1][1] = tailCoords[i + 1][1][1];
	}
}

void turn(int btn){
	if(btn & 2){
		turnRight();
	}else if(btn & 8){
		turnLeft();
	}
	return;
}

void turnRight(){
	if(xDir == 1){
		xDir = 0;
		yDir = 1;
	}else if (xDir == -1){
		xDir = 0;
		yDir = -1;
	}else if(yDir == 1){
		xDir = -1;
		yDir = 0;
	}else if(yDir == -1){
		xDir = 1;
		yDir = 0;
	} 
	return;
}

void turnLeft(){
	if(xDir == 1){
		xDir = 0;
		yDir = -1;
	}else if (xDir == -1){
		xDir = 0;
		yDir = 1;
	}else if(yDir == 1){
		xDir = 1;
		yDir = 0;
	}else if(yDir == -1){
		xDir = -1;
		yDir = 0;
	} 
	return;
}

int headHitApple(){
	int i;
	int j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(x[i] == appleCoords[j][0] && y[i] == appleCoords[j][1]){
				return 1;
			}
		}
	}
	return 0;
}

void increaseSnokLength(){
	int i;
	for(i = 0; i < getIncreaseLengthBy(); i++){
		if(removeTailIndex > storeTailIndex){
			shiftTailCoordsRight();
			incrementRemoveTailIndex();
		}
		incrementTailLengthIndex();
	}
	return;
}

void lightHead(){
	int i;
	for(i = 0; i < 4; i++){
		light(x[i], y[i]);
	}
	return;
}

int hitWall(){
	int i;
	for(i = 0; i < 4; i++){
		if(gameBackdrop[(y[i] / 8) * 128 + x[i]] & (1 << (y[i] - (y[i] / 8) * 8))){
			return 1;
		}
	}
	return 0;
}

void die(){
	resetTail();
	resetHead();
	resetApple();
	resetSettings();
	resetDirection();
	resetGameBackdrop();
	return;
}

void darkLastTailIndex(){
	dark(tailCoords[removeTailIndex][0][0], tailCoords[removeTailIndex][0][1]);
	dark(tailCoords[removeTailIndex][1][0], tailCoords[removeTailIndex][1][1]);
	return;
}

int getTailLengthIndex(){
	return tailLengthIndex;
}

int getCurrentTailLength(){
	return currentTailLength;
}

int getRemoveTailIndex(){
	return removeTailIndex;
}

int getStoreTailIndex(){
	return storeTailIndex;
}

void incrementStoreTailIndex(){
	storeTailIndex++;
	return;
}

void addDirToCoordinates(int index){
	y[index] += yDir;
	x[index] += xDir;
}

void incrementTailLengthIndex(){
	tailLengthIndex++;
	return;
}

void incrementRemoveTailIndex(){
	removeTailIndex++;
	return;
}

void decrementCurrentTailLength(){
	currentTailLength--;
	return;
}

void incrementCurrentTailLength(){
	currentTailLength++;
	return;
}

/**************************************************** RESETS **************************************************/

void resetHead(){
	int i;
	for(i = 0; i < 4; i++){
		x[i] = getStartPositionX()[i];
		y[i] = getStartPositionY()[i];
	}
	return;
}

void resetDirection(){
	xDir = 1;
	yDir = 0;
	return;
}

void resetStoreTailIndex(){
	storeTailIndex = 0;
	return;
}

void resetRemoveTailIndex(){
	removeTailIndex = 0;
	return;
}

void resetTailLengthIndex(){
	tailLengthIndex = (getSnokLength() - 1);
	return;
}

void resetCurrentTailLength(){
	currentTailLength = 0;
	return;
}

