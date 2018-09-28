/* Primary functions for running the game */

#include <stdint.h>
#include <pic32mx.h>
#include "snokheader.h"

void nextFrame(){
	moveSnok();
	if(headHitApple()){
		eatApple();
		
	}else if(hitWall()){
		die();
	}else{
		lightHead();
	}
	if(getCurrentTailLength() == getTailLengthIndex()){
		darkLastTailIndex();
		incrementRemoveTailIndex();
		decrementCurrentTailLength();
	}
	if(getStoreTailIndex() == getTailLengthIndex() + 1){
		resetStoreTailIndex();
	}
	if(getRemoveTailIndex() == getTailLengthIndex() + 1){
		resetRemoveTailIndex();
	}

}

void moveSnok(){
	moveX();
	moveY();
	incrementCurrentTailLength();
	return;
}

void eatApple(){
	increaseSnokLength();
		resetApple();
		lightHead();
		incrementApplesEaten();
		if(getApplesEaten() == getApplesForSpeedup()){
			resetApplesEaten();
			setGameSpeed(getGameSpeed() + getSpeedupBy());
		}
	return;
}

void spawnApple(){
	createAppleCoords();
	if(!appleOnSnok()){
		turnOnApple();
		lightApple();
	}
	return;
}









