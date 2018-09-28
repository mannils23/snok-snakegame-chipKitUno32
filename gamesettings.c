#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "snokheader.h"  /* Declatations for these labs */


int standardGameSpeed = 6000;
int standardSnokLength = 8;
int applesForSpeedup = 1; 			
int speedupBy = -150;				// negative for speedup
int increaseLengthBy = 7;

int startPositionX[] = {15,15,14,14};
int startPositionY[] = {15,16,15,16};

int gameSpeed = 5000;
int snokLength = 8;

void changeStandardGameSpeed( int newSpeed){
	standardGameSpeed += newSpeed;
	return;
}

void changeSpeedup(int newSpeedup){
	speedupBy += newSpeedup;
	return;
}

void changeGrowth(int growth){
	increaseLengthBy += growth;
	return;
}


int getIncreaseLengthBy(){
	return increaseLengthBy;
}

int getStandardSnokLength(){
	return standardSnokLength;
}

int getStandardGameSpeed(){
	return standardGameSpeed;
}

int getGameSpeed(){
	return gameSpeed;
}

void setGameSpeed(int newSpeed){
	gameSpeed = newSpeed;
	return;
}

int getSnokLength(){
	return snokLength;
}

void setSnokLength(int lentgh){
	snokLength = lentgh;
	return;
}

int* getStartPositionX(){
	return &startPositionX[0];
}

int* getStartPositionY(){
	return &startPositionY[0];
}

int getApplesForSpeedup(){
	return applesForSpeedup;
}

void setApplesForSpeedup(int amount){
	applesForSpeedup = amount;
	return;
}

int getSpeedupBy(){
	return speedupBy;
}
