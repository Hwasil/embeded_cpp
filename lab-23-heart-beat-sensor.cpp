#include <stdlib.h>
#include "mbed.h"

#define HEART_BEAT_PIN PB_1

AnalogIn hbSensor(HEART_BEAT_PIN);
Timer tmr;

void setup() {
	//tmr.start();
}

int main() {
		setup();
	
    while(1) {
//      float t = tmr.read();
//			printf("%f %f\r\n", sin(t), cos(t));
			printf("%f\r\n", hbSensor.read());
    }
		
}
