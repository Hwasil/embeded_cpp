#include "mbed.h"

#define BUZZER_PIN PC_9
#define RED_LED_PIN PA_4

//DigitalOut buzzer(BUZZER_PIN);
PwmOut buzzer(BUZZER_PIN);
DigitalOut redLed(RED_LED_PIN);

Timer buzzerTm;
Timer ledTm;

#define C_NOTE_HALF_PEREIOD 1915 // usec

void setup() {
	buzzer.period_us(C_NOTE_HALF_PEREIOD * 2);
	buzzer = 0.5; // 50% rate
	redLed = 0;
	
	buzzerTm.start();
	ledTm.start();
}

int main() {
		setup();
	
    while(1) {
			/*
			for (int i=0; i<400; i++) {	
				buzzer = 1;
				wait_us(C_NOTE_HALF_PEREIOD);
				buzzer = 0;
				wait_us(C_NOTE_HALF_PEREIOD);
			}
			wait(2.0);
			*/
			
			// LED blinky
			if (ledTm.read_ms() >= 500) {
				redLed = !redLed;
				ledTm.reset(); // re-search
			}
			
			// sound
			if (buzzerTm.read_ms() >= 1000) {
				buzzer = buzzer.read() == 0 ? 0.5 : 0;
				buzzerTm.reset();
			}
    }	
}
