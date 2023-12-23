#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define YELLO_LED_PIN PB_10
#define RED_LED_PIN PA_4

DigitalOut greenLed(GREEN_LED_PIN);
DigitalOut yelloLed(YELLO_LED_PIN);
DigitalOut redLed(RED_LED_PIN);

void setup() {  
	greenLed.write(0);
}


//BusOut ledBus (PA_13, PB_10, PA_4);
int ledMasks [] = {
	0b00000001, // only green on
	0b00000010, // only yello on
	0b00000100  // only red on
};

int main() {
	
  setup();
	
	// initialize all LEDs to be off
	//ledBus = 0;
	
	while(1) {
		/*
		//greenLed.write(1); // led on
		greenLed = 1;
		wait(0.5); // float, second
		
		//greenLed.write(0); // led off
		greenLed = 0;
		wait(0.5);
		
		yelloLed = 1;
		wait(0.5);
		yelloLed = 0;
		wait(0.5);
		
		redLed = 1;
		wait(0.5);
		redLed = 0;
		wait(0.5);
		*/
		
		//greenLed = !greenLed; // read operation
		//wait(0.5);
		
		
		
		for (int cnt=0; cnt<8; cnt++) {
			if (cnt & 0x01) redLed = 1;
			else redLed = 0;
			
			if (cnt & 0x02) yelloLed = 1;
			else yelloLed = 0;
			
			if (cnt & 0x04) greenLed = 1;
			else greenLed = 0;
			
			wait(1);
			
/*			
			ledBus = ledMasks[cnt];
			wait(1.0); // delay 1000 ms
*/
		}
	}
}
