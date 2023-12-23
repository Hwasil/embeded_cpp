la#include "mbed.h"

#define PIR_SENSOR_PIN D5
#define GREEN_LED_PIN PA_13
#define RED_LED_PIN PA_4
#define FIRST_BUTTON_PIN PA_14

Serial pc(USBTX, USBRX, 9600);
//DigitalIn pirSensor(PIR_SENSOR_PIN);
InterruptIn pirSensor(PIR_SENSOR_PIN);
DigitalOut light(GREEN_LED_PIN);
DigitalOut light2(RED_LED_PIN);
InterruptIn firstBtn(FIRST_BUTTON_PIN);

Timer tmr;
volatile long motionCnt = 0;
volatile int detected = 0;

typedef enum {
	NO_EDGE=0, RISING_EDGE, FALLING_EDGE 
} edge_t;

edge_t detectPIREdge() {
	static int prevState = 0;
	int currState = pirSensor;
	
	if (currState != prevState) {
		//wait_ms(50); // debouncing delay. Use only when button
		prevState = currState;
		return (currState == 1) ? RISING_EDGE: FALLING_EDGE;
	}
	return NO_EDGE;
}

void risingEdgeHandler() {
	light = 1;
	++motionCnt;
	detected = 1;
}

void fallingEdgeHandler() {
	light = 0;
}

void firstBtnIrqHandler() {
	light2 = !light2;
}

void setup() {
	light = 0;
	light2 = 0;
	tmr.start();
	
	pirSensor.rise(&risingEdgeHandler);
	pirSensor.fall(&fallingEdgeHandler);
	firstBtn.fall(&firstBtnIrqHandler);
}

int main() {
		setup();
	
    while(1) {
     /* edge_t edge = detectPIREdge(); // polling
			
				if (edge == RISING_EDGE) {
					light = 1;
					tmr.reset();
					pc.printf("Detect movement...\n");
				} 
				else if (edge == FALLING_EDGE) {
					light = 0;
					pc.printf("Delay time = %4.2f sec\n", tmr.read());
				}
			*/	
				// process oter tasks
				//light2 = !light2;
				wait(1.0);
			
				if (detected == 1) {
					pc.printf("Motion Count = %d\n", motionCnt);
					detected = 0;
			}
    }
		
}
