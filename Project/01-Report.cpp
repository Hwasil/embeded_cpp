#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define YELLOW_LED_PIN PB_10
#define RED_LED_PIN PA_4
#define FIRST_BTN_PIN PA_14
#define SECOND_BTN_PIN PB_7
#define THIRD_BTN_PIN PA_4

DigitalOut greenLed(GREEN_LED_PIN);
DigitalOut yellowLed(YELLOW_LED_PIN);
DigitalOut redLed(RED_LED_PIN);
DigitalIn firstBtn(FIRST_BTN_PIN);
DigitalIn secondBtn(SECOND_BTN_PIN);
DigitalIn thirdBtn(THIRD_BTN_PIN);

int ledBlinkyInterval = 1000;
int ledBlinkyColor = 0; // 0: Green, 1: Yellow, 2: Red
int ledBlinkyDir = 1; // 1: Up, -1: Down
Timer blinkyTm;

typedef enum {
	NO_EDGE=0, RISING_EDGE, FALLING_EDGE
} edge_t;

edge_t detectBtnEdge(DigitalIn& btn) {
	static int prevState = 1; 
	edge_t edge = NO_EDGE;
	
	int currState = btn;
	if (currState != prevState) {
		wait_ms(50); // debouncing delay 50 msec
		currState = btn;
		if (currState != prevState) {
			if (currState == 1) edge = RISING_EDGE;
			else edge = FALLING_EDGE;
			prevState = currState; // update (important)
		}
	}
	
	return edge;
}

void setup() {
	greenLed = 0;
	yellowLed = 0;
	redLed = 0;
	blinkyTm.start();
}

int main() {
	setup();
	
	while(1) {
		greenLed = 1;
		wait(1.0);
		greenLed = 0;
		wait(1.0);
		if (blinkyTm.read_ms() >= ledBlinkyInterval) {
			blinkyTm.reset();
			switch (ledBlinkyColor) {
				case 0:
					greenLed = !greenLed;
					break;
				case 1:
					yellowLed = !yellowLed;
					break;
				case 2:
					redLed = !redLed;
					break;
				default:
					break;
			}
		}
		
		if (detectBtnEdge(firstBtn) == FALLING_EDGE) {
			ledBlinkyInterval /= 2;
			if (ledBlinkyInterval < 50) ledBlinkyInterval = 50;
		}
		if (detectBtnEdge(secondBtn) == FALLING_EDGE) {
			ledBlinkyInterval *= 2;
			if (ledBlinkyInterval > 2000) ledBlinkyInterval = 2000;
		}
		if (detectBtnEdge(thirdBtn) == FALLING_EDGE) {
			ledBlinkyColor = (ledBlinkyColor + ledBlinkyDir + 3) % 3;
			if (ledBlinkyColor == 0) ledBlinkyDir = 1;
			if (ledBlinkyColor == 2) ledBlinkyDir = -1;
			greenLed = 0;
			yellowLed = 0;
			redLed = 0;
		}
	}
}
