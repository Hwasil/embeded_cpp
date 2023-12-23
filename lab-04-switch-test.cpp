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
        //if (firstBtn.read() == 0) 
/*				if (firstBtn == 0)
					greenLed = 1;
				else
					greenLed = 0;
		
				greenLed = firstBtn == 0 ? 1: 0;
	*/				
				greenLed = !firstBtn;
    }
		
}
