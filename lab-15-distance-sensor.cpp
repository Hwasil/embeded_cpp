#include "mbed.h"

#define IR_SENSOR_PIN PC_5

Serial pc(USBTX, USBRX, 9600);
AnalogIn irSensor(IR_SENSOR_PIN);

#define BTIGHTNESS_THRESHOLD 70

#define ALPHA 0.15

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


void setup() {
	pc.printf("--- IR Distance Sensor Test ---\n");
}
int main() {
		setup();
		
		double distance = 0;
		double volt = 0;
	
    while(1) {
      volt = LPF(irSensor.read());
			
			if (0.18 <= volt && volt <= 0.9) {
				distance = 26.663 * pow((volt * 3.3), -1.25);
				pc.printf("Distance = %5.2f cm\n", distance);
			} else {
				pc.printf("-------cm\n");
			}
			wait(0.3);
    }
		
}
