/* snokheader.h */
/* declare all global variables and functions necessary for snok to work */

/* Different backgrounds for game */
extern uint8_t gameBackdrop[512];
extern uint8_t menuBackground[512];
extern uint8_t settingsBackground[512];
extern uint8_t lightSpeed[512];

/* Global variables */
extern int timeoutCount;
extern int buttonDelay;
extern int randomNumber;
extern int appleCoords[4][2];


void gamework(void);
void checkSwitches(void);

/****GAMESETINGS******/
int getGameSpeed(void);
int getSnokLength(void);
int getStandardGameSpeed(void);
int getStandardSnokLength(void);
int* getStartPositionX(void);
int* getStartPositionY(void);
int getApplesForSpeedup(void);
int getIncreaseLengthBy(void);
void setApplesForSpeedup(int);
void setSnokLength(int);
void changeStandardgameSpeed(int);
void changeSpeedup(int);
void changeGrowth(int);


/********MENU*********/
void menu(void);					
void loadMenuBackground(void);
void waitForBtnsMenu(void);
void loadSelectorPlay(void);
void loadSelectorSettings(void);
void unloadSelectorMenu(void);

void settings(void);
void loadSettingsBackground(void);
void waitForBtnsSettings(void);
void loadSelectorSpeed(void);
void loadSelectorSpeedup(void);
void loadSelectorGrowth(void);
void loadSelectorReturn(void);
void unloadSelectorSettings(void);
void moveSelectorDown(void);
void moveSelectorUp(void);
void increaseBar(void);
void decreaseBar(void);
void increaseSpeedBar(void);
void increaseSpeedupBar(void);
void increaseGrowthBar(void);
void decreaseSpeedBar(void);
void decreaseSpeedupBar(void);
void decreaseGrowthBar(void);


/********GAME*********/
void nextFrame(void);
void moveSnok(void);
void eatApple(void);
void spawnApple(void);


/*********MOVE********/
void turn(int);
void turnRight(void);
void turnLeft(void);
void moveX(void);
void moveY(void);
void addDirToCoordinates(int);
int hitWall(void);
void die(void);
void storeTailCoords(int, int, int, int); 
void lightHead(void);
void darkTail(void);
void darkLastTailIndex(void);
int getTailLengthIndex(void);
int getCurrentTailLength(void);
int getRemoveTailIndex(void);
int getStoreTailIndex(void);
void incrementStoreTailIndex(void);
void incrementCurrentTailLength(void);
void incrementRemoveTailIndex(void);
void incrementTailLengthIndex(void);
void decrementCurrentTailLength(void);

void resetCoordinates(void);
void resetStoreTailIndex(void);
void resetRemoveTailIndex(void);
void resetTailLengthIndex(void);
void resetCurrentTailLength(void);
void resetDirection(void);
void resetHead(void);


/********APPLE********/
void createAppleCoords(void);
void turnOffApple(void);
void turnOnApple(void);
void lightApple(void);
void darkApple(void);
int isApple(void);
int appleExists(void);
int appleOnSnok(void);
int getApplesEaten(void);
void incrementApplesEaten(void);
void resetApplesEaten(void);


/********RESET*********/
void resetSettings(void);
void resetApple(void);
void resetImage(void);
void resetGameBackdrop(void);


/*********BOARDFUNC*********/
int getBtns(void);
int getSwitches(void);
void checkBtns(void);
void light(int, int);
void dark(int, int);
void boardInit(void);


/* Old stuff from lab, necessary for display to work */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
uint8_t spi_send_recv(uint8_t data);
char * itoaconv( int num );
void quicksleep(int cyc);


