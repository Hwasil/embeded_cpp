#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define FIRST_BTN_PIN PA_14

DigitalOut greenLed(GREEN_LED_PIN);
DigitalIn firstBtn(FIRST_BTN_PIN);

void setup() {
	greenLed = 0;
}

int main() {
		setup();
	
    while(1) {
        if (firstBtn == 0) {
					wait(0.1); // debouncing delay
					greenLed = !greenLed;
					
					wait(0.5);
				}				   
		}
		
}
