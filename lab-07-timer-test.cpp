#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define FIRST_BTN_PIN PA_14

DigitalOut greenLed(GREEN_LED_PIN);
DigitalIn firstBtn(FIRST_BTN_PIN);

int ledBlinky = 1;  
Timer blinkyTm;

typedef enum {
	NO_EDGE=0, RISING_EDGE, FALLING_EDGE
} edge_t;

edge_t detectFirstBtnEdge() {
	static int prevState = 1; 
	edge_t edge = NO_EDGE;
	
	int currState = firstBtn;
	if (currState != prevState) {
		wait_ms(50);                  //debouncing delay 50 msec
		currState = firstBtn;
		if (currState != prevState) {
			if (currState == 1) edge = RISING_EDGE;
			else edge = FALLING_EDGE;
			prevState = currState;         //update (important)
		}
	}
	
	return edge;
}

void setup() {
	greenLed = 0;
	blinkyTm.start();
}

int main() {
		setup();
	
    while(1) {
			if (ledBlinky) {
				if (blinkyTm.read_ms() >= 500) {
					blinkyTm.reset();
					greenLed = !greenLed;
				}
			}
			
			if (detectFirstBtnEdge() == FALLING_EDGE) {
				ledBlinky = !ledBlinky;
				blinkyTm.reset();
			}
		}
}
