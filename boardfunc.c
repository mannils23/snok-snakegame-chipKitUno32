#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "snokheader.h"  /* Declatations for these labs */

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

#define TMR2PERIOD ((80000000 / 64) / 100000)
#if TMR2PERIOD > 0xffff
#error "Timer_period_is_too_big."
#endif

int timeoutCount = 0;
int buttonDelay = 0;


void boardInit(){
	PORTD = (PORTD | 0x0e0);	// initiate buttons in register
	PORTF = (PORTF | 0x002);
	PORTD = (PORTD | 0x0f00); // ini switches

	T2CON = 0;				// Clear T2CON, set all bits to 0
	T2CONSET = 0x060;		// Activate 64-prescale
	PR2 = TMR2PERIOD;		// Set period register
	TMR2 = 0;				// Define timer start value

	IEC(0) = (IEC(0) | (0x1 << 8));			// Enable interrupt for timer 2					T2IE
	IPC(2) = (IPC(2) | 0x03);				// Set sub-priority to highest (3)				T2IS			T2IF is in IFS(0) on bit 8
	IPC(2) = (IPC(2) | (0x07 << 2)); 		// Set priority to highest (7)					T2IP
	asm volatile ("ei");					// enable interrupts on the micro-controller						
	T2CONSET = 0x8000;		// Start the timer
	return;
}

void user_isr( void ){
	if((IFS(0) >> 8) & 0x01){					
		timeoutCount++;
		randomNumber++;
		IFS(0) = (IFS(0) & 0xfeff);				
	}
  return;
}

int getBtns(void){
	return (((PORTD & 0x0e0) >> 4) | ((PORTF & 0x02) >> 1));
}

int getSwitches(void){
	return ((PORTD & 0x0f00) >> 8);
}

void light (int locx, int locy){
		short offset = 0;
		if (locy > 0){
			offset = (locy / 8);
		}
		gameBackdrop[offset * 128 + locx] = gameBackdrop[offset * 128 + locx] | (1 << (locy - offset * 8));
		return;
	}

void dark(int locx, int locy){
		gameBackdrop[(locy / 8) * 128 + locx] = gameBackdrop[(locy / 8) * 128 + locx] & ~(1 << (locy - (locy / 8) * 8));
		return;
}


/*****************************************************************************************************/
/********************************* necessary code from labs ******************************************/
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
} 
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void display_image(int x, const uint8_t *data) {
  int i, j;
  
  for(i = 0; i < 4; i++) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;

    spi_send_recv(0x22);
    spi_send_recv(i);
    
    spi_send_recv(x & 0xF);
    spi_send_recv(0x10 | ((x >> 4) & 0xF));
    
    DISPLAY_CHANGE_TO_DATA_MODE;
    
    for(j = 0; j < 128; j++)
      spi_send_recv(data[(i*128) + j]);
  }
}
