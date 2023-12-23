#include "mbed.h"
#include "motordriver.h"

#define JS_X_AXIS PC_2
#define JS_Y_AXIS PC_3
#define MOTOR_A_PWM_PIN D11
#define MOTOR_A_DIR_PIN PC_8

Serial pc(USBTX, USBRX, 9600); //port number
AnalogIn xAxis(JS_X_AXIS);
AnalogIn yAxis(JS_Y_AXIS);

Motor motorA(MOTOR_A_PWM_PIN, MOTOR_A_DIR_PIN);

Ticker controlTicker;
Ticker jsTicker;

int x, y;

#define NEUTRAL_VALUE 71 // mine

void readJoystick() {
	x = xAxis * 100;
	y = yAxis * 100;
	
	x = NEUTRAL_VALUE - x;
	if (abs(x) <= 2) x = 0;
	
	y = NEUTRAL_VALUE - y;
	if (abs(y) <= 2) y = 0;
}

void controlMotor() {
	if (x > 0) motorA.setDir(FORWARD_DIR);
	else if (x < 0) motorA.setDir(BACKWARD_DIR);
	
	if (y > 0) motorA.incSpeed(0.05);
	else if (y < 0) motorA.decSpeed(0.05);
	
}

void setup() {
	jsTicker.attach(&readJoystick, 0.2);
	controlTicker.attach(&controlMotor, 0.5);
}

int main() {
		setup();
	
    while(1) {
			/*
			readJoystick();
			pc.printf("JS X : %d, Y : %d\n", x, y);
			wait(0.3);
			*/
			
			// process other tasks
			wait(3.0);
    }
		
}
