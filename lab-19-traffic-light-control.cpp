#include "mbed.h"
#include "button_input.h"
#include "light_control.h"

enum { A, AtoB, B, BtoA } state;

#define PASS_WAIT_TIME 5 // 30
#define TRANS_WAIT_TIME 2 // 5
Ticker waitTimer;
int wait_time = 0 ;

void waitTimerHandler() {
	wait_time--;
}

void setup() {
	state = A;
	wait_time = PASS_WAIT_TIME;
	waitTimer.attach(&waitTimerHandler, 1.0);
}

int main() {
		setup();
		
    while(1) {
       switch (state) {
				 case A : 
						controlLightA(GREEN);
						controlLightB(RED);
						if (wait_time <= 0 || btnPressed() == BTN3) {
								state = AtoB;
								wait_time = TRANS_WAIT_TIME;
						}
						break;
				 case AtoB :
						controlLightA(YELLOW);
						controlLightB(RED);
						if (wait_time <= 0 || btnPressed() == BTN3) {
								state = B;
								wait_time = TRANS_WAIT_TIME;
						}
						break;
				 case B :
						controlLightA(RED);
						controlLightB(GREEN);
						if (wait_time <= 0 || btnPressed() == BTN3) {
								state = BtoA;
								wait_time = TRANS_WAIT_TIME;
						}
						break;
				 case BtoA :
						controlLightA(RED);
						controlLightB(YELLOW);
						if (wait_time <= 0 || btnPressed() == BTN3) {
								state = A;
								wait_time = TRANS_WAIT_TIME;
						}
						break;
			 }
    }		
}
