#include "mbed.h"

#define RGB_RED_PIN 		A1
#define RGB_GREEN_PIN 	PC_6
#define RGB_BLUE_PIN 		A3

PwmOut r(RGB_RED_PIN);
PwmOut g(RGB_GREEN_PIN);
PwmOut b(RGB_BLUE_PIN);

void setup() {
	r.period(0.001); // period = 1 msec, frequency = 1000 Hr
	g.period(0.001);
	b.period(0.001);
	r = 0;
	g = 0;
	b = 0;
}

int main() {
		setup();
	
    while(1) {
        for (double i=0; i<=1.0; i+=0.001) {
					double p = i * 3;
					r = (p<=1.0 ? (1-p) : ((p<=2.0) ? 0 : (p-2)));
					g = (p<=1.0 ? p : ((p<=2.0) ? 1 : (3-p)));
					b = (p<=1.0 ? 0 : ((p<=2.0) ? (p-1) : (3-p)));
					wait(0.01);
				}
    }	
}
