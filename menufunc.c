#include <stdint.h>
#include <pic32mx.h>
#include "snokheader.h"

int selector[3] = {93, 93, 93};					// values for display, light selector inside circle
int emptySelector[3] = {65, 65,65};				// values for display, empty circle
int fullBar = 62;								// value for display, fill light inside bar
int emptyBar = 34;								// value for display, empty inside bar
int posMenu = 0;								// keeps track on position of selector in "menu"
int posSettings = 0;							// keeps track on position of selector in "settings"
int btnPressed = 0;								// tells if any buttons is currently pressed
int start = 0;									// tells when to break out of menu loop and return (go to game)


/***************************************************************************/
/************************************ MENU**********************************/
void loadMenuBackground(){					
	display_image(0, menuBackground);
	return;
}

void menu(){					
	
	while(!start){					// Loads menu background and selector and jumps to waitForBtns loop
		loadMenuBackground();		// loops while start == 0, start is set to 1 when "play" option is chosen.
		loadSelectorPlay();			// this enables the user to "go back" to the menu from "settings".
		waitForBtnsMenu();
	}
	start = 0;						// sets start to 0 to enable loop for next time menu is called
	resetSettings();				// sets active game settings to default settings which may have been changed through options in "settings"
	return;							// this applies the changes to the game
}

void waitForBtnsMenu(){				// waits for user input and takes action accordingly
	while(1){
		if(getBtns() == 0){			// if no button is pressed, resets variable to enable inputs
			btnPressed = 0;
		}
		if(getBtns() & 2 && btnPressed == 0){		// user moved right, loads selector for "settings"
			btnPressed = 1;
			unloadSelectorMenu();
			loadSelectorSettings();
		}
		if(getBtns() & 8 && btnPressed == 0){		// user moved left, loads selector for "play"
			btnPressed = 1;
			unloadSelectorMenu();
			loadSelectorPlay();
		}
		if((getBtns() & 4) && posMenu == 1 && btnPressed == 0){		// user chose "settings", calls function for settings
			btnPressed = 1;
			settings();
			break;
		}
		if( (getBtns() & 4) && (posMenu == 0) && btnPressed == 0 ){		// user chose "play", sets start = 1 to break menu-loop, then returns
			start = 1;
			return;
		}
	}
	return;
}

void loadSelectorPlay(){				// loads selector for "menu"
	unloadSelectorMenu();
	int i;
	for(i = 0; i < 3; i++){
		menuBackground[271 + i] = selector[i];
	}
	posMenu = 0;
	loadMenuBackground();
	return;
}

void loadSelectorSettings(){			// loads selector for "settings"
	unloadSelectorMenu();
	int i;
	for(i = 0; i < 3; i++){
		menuBackground[331 + i] = selector[i];
	}
	posMenu = 1;
	loadMenuBackground();
	return;
}

void unloadSelectorMenu(){				// removes both selectors from display
	int i;
	for(i = 0; i < 3; i++){
		menuBackground[271 + i] = emptySelector[i];
		menuBackground[331 + i] = emptySelector[i];
	}
	loadMenuBackground();
}


/********************************************************************************/
/************************************ SETTINGS **********************************/


void settings(){					// loads settings background and selector for "return"
	loadSettingsBackground();
	loadSelectorReturn();
	waitForBtnsSettings();			// calls for waitForBtnsSettings
	return;
	
}

void loadSettingsBackground(){
	display_image(0, settingsBackground);
	return;
}

void waitForBtnsSettings(){			// loops and waits for user input
	while(1){
		
		
		if(getBtns() & 2 && btnPressed == 0){	// button "down", move selecor down
			btnPressed = 1;
			moveSelectorDown();
		}
		else if(getBtns() & 8 && btnPressed == 0){		// button "up", move selector up
			btnPressed = 1;
			moveSelectorUp();
		}
		else if(getBtns() & 1 && btnPressed == 0){		// "increase bar" pressed, increase bar at current position
			btnPressed = 1;
			increaseBar();
		}

		else if(getBtns() & 4 && btnPressed == 0){		// "decrease bar" pressed, increase bar at current position
			btnPressed = 1;
			if(posSettings == 3){					// if current position is "return", break loop
				break;
			}
			decreaseBar();
		}

		else if(getBtns() == 0){		// if no button is pressed, increase the buttonDelay, this is to prevent several inputs in one click
			buttonDelay++;
			if(buttonDelay > 30000){
				btnPressed = 0;
				buttonDelay = 0;
			}
		}
	}
	return;
}

void moveSelectorUp(){
	if(posSettings == 3){
		unloadSelectorSettings();
		loadSelectorGrowth();
	}
	else if(posSettings == 2){
		unloadSelectorSettings();
		loadSelectorSpeedup();
	}
	else if(posSettings == 1){
		unloadSelectorSettings();
		loadSelectorSpeed();
	}
	return;
}

void moveSelectorDown(){
	if(posSettings == 0){
		unloadSelectorSettings();
		loadSelectorSpeedup();
	}
	else if(posSettings == 1){
		unloadSelectorSettings();
		loadSelectorGrowth();
	}
	else if(posSettings == 2){
		unloadSelectorSettings();
		loadSelectorReturn();
	}
	return;
}

void loadSelectorSpeed(){
	int i;
	int j = 0;
	for(i = 15; i < 18; i++){
		settingsBackground[i] = selector[j];
		j++;
	}
	posSettings = 0;
	loadSettingsBackground();
}

void unloadSelectorSettings(){
	int i;
	int j = 0;
	for(i = 0; i < 3; i++){
		settingsBackground[15 + i] = emptySelector[j];
		settingsBackground[143 + i] = emptySelector[j];
		settingsBackground[271 + i] = emptySelector[j];
		settingsBackground[399 + i] = emptySelector[j];
		j++;
	}
	loadSettingsBackground();
}

void loadSelectorSpeedup(){
	int i;
	int j = 0;
	for(i = 143; i < 146; i++){
		settingsBackground[i] = selector[j];
		j++;
	}
	posSettings = 1;
	loadSettingsBackground();
}

void unloadSelectorSpeedup(){
	int i;
	int j = 0;
	for(i = 143; i < 146; i++){
		settingsBackground[i] = emptySelector[j];
		j++;
	}
	loadSettingsBackground();
}

void loadSelectorGrowth(){
	int i;
	int j = 0;
	for(i = 271; i < 274; i++){
		settingsBackground[i] = selector[j];
		j++;
	}
	posSettings = 2;
	loadSettingsBackground();
}

void unloadSelectorGrowth(){
	int i;
	int j = 0;
	for(i = 271; i < 274; i++){
		settingsBackground[i] = emptySelector[j];
		j++;
	}
	loadSettingsBackground();
}

void loadSelectorReturn(){
	int i;
	int j = 0;
	for(i = 399; i < 402; i++){
		settingsBackground[i] = selector[j];
		j++;
	}
	posSettings = 3;
	loadSettingsBackground();
}

void unloadSelectorReturn(){
	int i;
	int j = 0;
	for(i = 399; i < 402; i++){
		settingsBackground[i] = emptySelector[j];
		j++;
	}
	loadSettingsBackground();
}

void increaseBar(){
	if(posSettings == 0){
		increaseSpeedBar();
	}
	if(posSettings == 1){
		increaseSpeedupBar();
	}
	if(posSettings == 2){
		increaseGrowthBar();
	}
	display_image(0, settingsBackground);
	return;
}

void decreaseBar(){
	if(posSettings == 0){
		decreaseSpeedBar();
	}
	if(posSettings == 1){
		decreaseSpeedupBar();
	}
	if(posSettings == 2){
		decreaseGrowthBar();
	}
	display_image(0, settingsBackground);
	return;
}

void increaseSpeedBar(){
	int i;
	for(i = 0; i < 50; i++){
		if(settingsBackground[74 + i] == 34){
			break;
		}
	}
	int j;
	if((i-1) < 40){
		for(j = 0; j < 10; j++){
			settingsBackground[74 + i + j] = fullBar; 		
		}
		changeStandardGameSpeed(-1000);
	}
	return;
}

void increaseSpeedupBar(){
	int i;
	
	for(i = 0; i < 50; i++){
		if(settingsBackground[202 + i] == 34){
			break;
		}
	}
	int j;
	if((i-1) < 40){
		for(j = 0; j < 10; j++){
			settingsBackground[202 + i + j] = fullBar;		//201
		}
		changeSpeedup(-50);
	}
	return;
}

void increaseGrowthBar(){
	int i;
	for(i = 0; i < 50; i++){
		if(settingsBackground[330 + i] == 34){
			break;
		}
	}
	int j;
	if((i-1) < 40){
		for(j = 0; j < 10; j++){
			settingsBackground[330 + i + j] = fullBar;
		}
		changeGrowth(2);
	}
	return;
}

void decreaseSpeedBar(){
	int i;
	for(i = 49; i > -1; i--){
		if(settingsBackground[74 + i] == 62){
			break;
		}
	}
	int j;
	if(i > 8){
		for(j = 0; j < 10; j++){
			settingsBackground[74 + i - j] = emptyBar;		//201
		}
		changeStandardGameSpeed(1000);
	}
	return;
}

void decreaseSpeedupBar(){
	int i;
	for(i = 49; i > -1; i--){
		if(settingsBackground[202 + i] == 62){
			break;
		}
	}
	int j;
	if(i > 8){
		for(j = 0; j < 10; j++){
			settingsBackground[202 + i - j] = emptyBar;		//201
		}
		changeSpeedup(50);
	}
	
	return;
}

void decreaseGrowthBar(){
	int i;
	for(i = 49; i > -1; i--){
		if(settingsBackground[330 + i] == 62){
			break;
		}
	}
	int j;
	if(i > 8){
		for(j = 0; j < 10; j++){
			settingsBackground[330 + i - j] = emptyBar;		//201
		}
		changeGrowth(-2);
	}
	
	
	return;
}