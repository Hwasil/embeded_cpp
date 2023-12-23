#ifndef _BUTTON_INPUT_
#define _BUTTON_INPUT_

#include "mbed.h"

typedef enum { NONE=0, BTN1=1, BTN2=2, BTN3=4, BTN12=3, BTN13=5, BTN23=6, BTN123=7 } btn_input_t;
BusIn btnBus(PC_4, PB_7, PA_14); // input 16bit but don't mind, only 3 values

btn_input_t btnPressed() {
	static int prevState = 0xffff;
	int currState = btnBus;
	
	if (currState != prevState) {
		wait_ms(100); // debouncing delay
		prevState = currState;
		return (btn_input_t)(~currState & 0x07);
	}
	
	return NONE; // anything not pressed
}

#endif