#include "mbed.h"

#define CDS_SENSOR_PIN A0
#define GREEN_LED_PIN PA_13

Serial pc(USBTX, USBRX, 9600);
AnalogIn cdsSensor(CDS_SENSOR_PIN);
DigitalOut light(GREEN_LED_PIN);

#define BTIGHTNESS_THRESHOLD 70

#define ALPHA 0.2

double LPF(double meas) {
	static double prevValue = -1;
	double value = 0;
	
	if (prevValue < 0) {
		prevValue = meas;
	}
	value = (1.0 - ALPHA) * prevValue + ALPHA * meas;
	prevValue = meas;
	
	return value;
}

double AverageFilter() {
	double values = 0;
	for (int i=0; i<10; i++) {
		values += cdsSensor.read();
		wait_ms(10);
	}
	return values/10;
}

void setup() {
	pc.printf("--- cds Sensor Test ---\n");
	light = 0;
}
int main() {
		setup();
	
    while(1) {
      double brightness = LPF(cdsSensor.read()) * 100;
			pc.printf("Brightness = %5.2f\n", brightness);
			if (brightness >= BTIGHTNESS_THRESHOLD) {
				light = 1;
			} else {
				light = 0;
			}
			wait(0.5);
    }
		
}
