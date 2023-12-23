#include "mbed.h"

#define MIC_PIN A5
#define GREEN_LED_PIN PA_13

Serial pc(USBTX, USBRX, 9600);
AnalogIn mic(MIC_PIN);
DigitalOut greenLed(GREEN_LED_PIN);

#define SOUND_THRESHOLD 80
void setup() {
	greenLed = 0;
}

int main() {
		setup();
	
    while(1) {
			double laudness = mic.read() * 100;
			if (laudness >= SOUND_THRESHOLD) {
				pc.printf("Laudness = %f \n", laudness);
				greenLed = !greenLed;
			}
			wait(0.5);
    }
		
}
