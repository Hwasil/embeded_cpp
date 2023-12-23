#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define YELLOW_LED_PIN PB_10
#define RED_LED_PIN PA_4
#define FIRST_BTN_PIN PA_14
#define SECOND_BTN_PIN PB_7

BusOut ledBus(RED_LED_PIN, YELLOW_LED_PIN, GREEN_LED_PIN);
DigitalIn firstBtn(FIRST_BTN_PIN);
DigitalIn resetBtn(SECOND_BTN_PIN);

enum { STATE0=0, STATE1, STATE2, STATE3, STATE4, STATE5, STATE6, STATE7 } state;

int checkFirstBtnPressed() {
	static int prevState = 1;
	int currState = firstBtn;
	
	if (currState != prevState) {
		wait_ms(100); // debouncing delay
		prevState = currState;
		if (currState == 0) {
			return 1;
		}
	}
	return 0;
}

int checkResetBtnPressed() {
	static int prevState = 1;
	int currState = resetBtn;
	
	if (currState != prevState) {
		wait_ms(100); // debouncing delay
		prevState = currState;
		if (currState == 0) {
			return 1;
		}
	}
	return 0;
}

void setup() {
	state = STATE0;
}

int main() {
		setup();
	
    while(1) {
			switch (state) {
				case STATE0 :
					// actions in curent state == LED On
					ledBus = 0;
					// check state trasition codition
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE1;
					}
					break;
				case STATE1 :
					ledBus = 1;
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE2;
					}
					break;
				case STATE2 :
					ledBus = 2;
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE3;
					}
					break;
				case STATE3 :
					ledBus = 3;
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE4;
					}
					break;
				case STATE4 :
					ledBus = 4;
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE5;
					}
					break;
				case STATE5 :
					ledBus = 5;
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE6;
					}
					break;
				case STATE6 :
					ledBus = 6;
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE7;
					}
					break;
				case STATE7 :
					ledBus = 7;
					if (checkResetBtnPressed()) {
						state = STATE0;
					}
					else if (checkFirstBtnPressed()) {
						state = STATE0;
					}
					break;
    }
	}
}
