#include "motordrive.h"

#define MOTOR_STOP					0
#define MOTOR_CM_ROTATION			1
#define MOTOR_CCM_ROTATION			-1

#define FORWARD_DIR					0
#define BACKWORD_DIR				1

Motor::Motor(PinName pwm, PinName dir):
	_pwm(pwm), _dir(dir)
{
	_pwm.period(0.001);			//	f = 1000Hz
	_pwm = 0;								//_pwm.write(0);
	
	_dir = FORWARD_DIR;
	_sign = MOTOR_STOP;
}

void Motor::forward(double speed) {
	if (_sign == MOTOR_CCM_ROTATION) {
		_pwm = 0;
		wait(0.2);
	}
	
	_dir = FORWARD_DIR;
	_pwm = (speed < 0) ? 0 : ((speed > 1) ? 1.0 : speed);
	_sign = MOTOR_CM_ROTATION;
}

void Motor::backword(double speed) {
	if (_sign == MOTOR_CM_ROTATION) {
		_pwm = 0;
		wait(0.2);
	}
	
	_dir = BACKWORD_DIR;
	_pwm = (speed < 0) ? 0 : ((speed > 1) ? 1.0 : speed);
	_sign = MOTOR_CCM_ROTATION;
}

void Motor::stop() {
		_pwm = 0;
		_sign = MOTOR_STOP;
}

// add
double Motor::getSpeed(){
	return _pwm;
}

double Motor::getDir(){
	return _dir;
}