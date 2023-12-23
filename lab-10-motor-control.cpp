#include "mbed.h"
#include "motordriver.h"

#define MOTOR_A_RWM_PIN PA_7
#define MOTOR_A_DIR_PIN PC_8

Motor motorA(MOTOR_A_RWM_PIN, MOTOR_A_DIR_PIN);

void setup() {
	motorA.stop();
}

int main() {
		setup();
	
    while(1) {
			for (double s =0; s<=1; s+=0.05) {
				motorA.forward(s);
				wait(0.3);
			}
			wait(1);
			
			for (double s =1.0; s>=0; s-=0.05) {
				motorA.forward(s);
				wait(0.3);
			}
			wait(1);
			
			for (double s =0; s<=1; s+=0.05) {
				motorA.backward(s);
				wait(0.3);
			}
			wait(1);
			
			for (double s =1.0; s>=0; s-=0.05) {
				motorA.backward(s);
				wait(0.3);
			}
			wait(1);
    }
		
}
