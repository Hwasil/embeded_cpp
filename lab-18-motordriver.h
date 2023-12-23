#include "motordriver.h"

#define MOTOR_STOP				  0
#define MOTOR_CW_ROTATION   1
#define MOTOR_CCW_ROTATION -1

Motor::Motor (PinName pwm, PinName dir) :
	_pwm(pwm), _dir(dir)
{
	// important
	_pwm.period(0.001); // f = 1000Hz
	_pwm.write(0);      // == _pwm.write(0);
	
	_dir = FORWARD_DIR;
	_sign = MOTOR_STOP;
}

void Motor::forward(double speed) {
	if (_sign == MOTOR_CCW_ROTATION) {
		_pwm = 0; //stop
		wait(0.2);
	}
	
	_dir = FORWARD_DIR;
	_pwm = (speed < 0) ? 0 : ((speed > 1) ? 1.0 : speed); 
}

void Motor::backward(double speed) { // try
	if (_sign == MOTOR_CW_ROTATION) {
		_pwm = 0; //stop
		wait(0.2);
	}
	
	_dir = BACKWARD_DIR;
	_pwm = (speed < 0) ? 0 : ((speed > 1) ? 1.0 : speed);
	_sign = MOTOR_CCW_ROTATION;
}

void Motor::stop() { 
	_pwm = 0; //stop
	_sign = MOTOR_STOP;
}

void Motor::setDir(int dir) {
	if (_sign == MOTOR_STOP) {
		_dir = dir;
	} else if (_dir != dir) {
		double speed = _pwm; // current value save
		_pwm = 0; // stop
		wait(0.1);
		_dir = dir; 
		_pwm = speed; // reStart
	}
}

void Motor::incSpeed(double step) {
	double speed = _dir;
	speed += step;
	if (speed < 0) speed=0;
	else if (speed > 1.0) speed = 1.0;
	_pwm = speed;
}

void Motor::decSpeed(double step) {
	double speed = _dir;
	speed -= step;
	if (speed < 0) speed=0;
	else if (speed > 1.0) speed = 1.0;
	_pwm = speed;
}
