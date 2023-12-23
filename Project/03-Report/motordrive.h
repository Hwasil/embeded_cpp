#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "mbed.h"

class Motor {
	public:
		Motor(PinName pwm, PinName dir);
		void forward(double speed);
		void backword(double speed);
		void stop();
	
	private:
		PwmOut _pwm;
		DigitalOut _dir;
		int _sign;
};

#endif		// MOTORDRIVER_H
