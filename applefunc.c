#include <stdint.h>
#include <pic32mx.h>
#include "snokheader.h"

int apple = 0;
int appleCoords[4][2];
int applesEaten = 0;

int appleExists(){
	return apple;
}

void turnOffApple(){
	apple = 0;
}

void turnOnApple(){
	apple = 1;
}

int getApplesEaten(){
	return applesEaten;
}

void incrementApplesEaten(){
	applesEaten++;
}

void resetApplesEaten(){
	applesEaten = 0;
}

void darkApple(){
	int i;
	for(i = 0; i < 4; i++){
			dark(appleCoords[i][0], appleCoords[i][1]);
	}
	return;
}

void lightApple(){
	int i;
	for(i = 0; i < 4; i++){
		light(appleCoords[i][0], appleCoords[i][1]);
	}
	return;
}

void createAppleCoords(){
	appleCoords[0][0] = ((randomNumber % 124) + 2);
	appleCoords[0][1] = ((randomNumber % 28) + 1);

	appleCoords[1][0] = appleCoords[0][0];
	appleCoords[1][1] = appleCoords[0][1] + 1;

	appleCoords[2][0] = appleCoords[0][0] - 1;
	appleCoords[2][1] = appleCoords[0][1];

	appleCoords[3][0] = appleCoords[0][0] - 1;
	appleCoords[3][1] = appleCoords[0][1] + 1;
	return;
}

int appleOnSnok(){
	int i;
	int j;
	for(i = 0; i < 4; i++){
		if(gameBackdrop[(appleCoords[i][1] / 8) * 128 + appleCoords[i][0]] & (1 << (appleCoords[i][1] - (appleCoords[i][1] / 8) * 8))){
			return 1;
		}
	}
	return 0;
}
