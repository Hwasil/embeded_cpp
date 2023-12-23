#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define FIRST_BTN_PIN PA_14

#define YELLOW_LED_PIN PB_10
#define SECOND_BTN_PIN PB_14

#define RED_LED_PIN PA_4
#define THIRD_BTN_PIN PA_14

DigitalOut greenLed(GREEN_LED_PIN);
DigitalIn firstBtn(FIRST_BTN_PIN);

DigitalOut yellowLed(YELLOW_LED_PIN);
DigitalIn secondBtn(SECOND_BTN_PIN);

DigitalOut redLed(RED_LED_PIN);
DigitalIn thirdBtn(THIRD_BTN_PIN);

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
}

int main() {
		
		setup();
	
    while(1) {
			// (1)
			greenLed = 1; 
			wait(1.0);
			greenLed = 0;
			wait(1.0);
			
			// (2)
			if (!firstBtn) { // fast
				greenLed = 1; 
				wait(0.05);
				greenLed = 0;
				wait(0.05);
			} else if (!secondBtn) { // slow
				greenLed = 1; 
				wait(2.0);
				greenLed = 0;
				wait(2.0);
			} else if (!thirdBtn) { // change color
				
			}
			
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
