#include "mbed.h"

#define GREEN_LED_PIN PA_13
#define YELLOW_LED_PIN PB_10
#define RED_LED_PIN PA_4

BusOut ledBus(RED_LED_PIN, YELLOW_LED_PIN, GREEN_LED_PIN);

void setup() {  
	ledBus.write(0);
}

int main() {
	
  setup();
	
	while(1) {
		for (int cnt=0; cnt<8; cnt++) {
			ledBus = cnt;
			
			wait(1);
		}
	}
}
