#include "mbed.h"

#define URF_TRIG_PIN PB_6
#define URF_ECHO_PIN PA_8

Serial pc(USBTX, USBRX, 9600);
DigitalOut urfTrig(URF_TRIG_PIN);
DigitalIn urfEcho(URF_ECHO_PIN);
Timer tmr1;

int pulseLength; // usec
float dist;      // cm

#define TRNSFORM_CONSTANT 0.01724 // 

void setup() {
	urfTrig = 0;
	tmr1.start();
}

int main() {
		setup();
	
    while(1) {
			// send TRIG signal to SRF-04
			urfTrig = 1;
			wait_us(40); // microsecond
			urfTrig = 0;
			
			// wait for echo signal to be high
			while (!urfEcho);
			
			// measure pulse length of ECHO signal
			tmr1.reset();
			while (urfEcho);
			pulseLength = tmr1.read_us();
			dist = pulseLength / 58.0; //ultrasonic moving 1s = 85cm?
			
			// output pulse length and distance to PC
			pc.printf("Pulse length = %d usec\n", pulseLength);
			pc.printf("Distance = %4.1f cm\n\n", dist);
			
			wait(1.0);
    }
		
}
