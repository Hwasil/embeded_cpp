#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define YELLOW_LED_PIN PB_10

DigitalOut greenLed(GREEN_LED_PIN);
DigitalOut yellowLed(YELLOW_LED_PIN);

//Timer fastTm;
//Timer slowTm;

//Timeout fastTimeout;
//Timeout slowTimeout;

Ticker fastTicker;
Ticker slowTicker;

void fast_task() {
	greenLed = !greenLed;
	//fastTimeout.attach(&fast_task, 0.2);
}

void slow_task() {
	yellowLed = !yellowLed; 
	//slowTimeout.attach(&slow_task, 1.0);
}

void setup() {
	//fastTm.start();
	//slowTm.start();
	
	//fastTimeout.attach(&fast_task, 0.2);
	//slowTimeout.attach(&slow_task, 1.0);
	
	fastTicker.attach(&fast_task, 0.2);
	slowTicker.attach(&slow_task, 1.0);
}

int main() {
		setup();
	
    while(1) {
		/*
       if (fastTm.read() >= 0.2) { // polling 
				 fast_task();
				 fastTm.reset();
			 }
			 
			 if (slowTm.read() >= 1.0) { 
				 slow_task();
				 slowTm.reset();
			 }
		*/
			
			// process other tasks
			wait(3.0);
    }
}
