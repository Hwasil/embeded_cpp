#include "mbed.h"
#include "motordrive.h"

#define MOTOR_A_PWM_PIN	PA_7
#define MOTOR_A_DIR_PIN	PC_8

#define FIRST_BTN_PIN PA_14
#define SECOND_BTN_PIN PB_7
#define THIRD_BTN_PIN PC_4

#define INTAVAL 0.05

Motor motorA(MOTOR_A_PWM_PIN, MOTOR_A_DIR_PIN);
DigitalIn firstBtn(FIRST_BTN_PIN);
DigitalIn secondBtn(SECOND_BTN_PIN);
DigitalIn thirdBtn(THIRD_BTN_PIN);

double speed;

void setup() {
	speed = 0.5;
	motorA.forward(speed);
}
//switch1 > toggle
//2> agree
//3 degree
//2+3>> stop
void toggle(){
	speed = motorA.getSpeed();
	if (motorA.getDir()== 0) //forward
		motorA.backword(speed);
	else
		motorA.forward(speed);
}

void increase(){
	speed = motorA.getSpeed()+INTAVAL;
	if(motorA.getDir()== 0)
		motorA.forward(speed);
	else
		motorA.backword(speed);
}

void decrease(){
	speed = motorA.getSpeed()- INTAVAL;
	if(motorA.getDir()== 0)
		motorA.forward(speed);
	else
		motorA.backword(speed);
}

int main() {
	setup();
	
	while(1){
		if(!firstBtn.read())
			toggle();
		else if(!secondBtn && !thirdBtn)
			motorA.stop();
		else if(!secondBtn.read())
			increase();
		else if(!thirdBtn.read())
			decrease();
		wait(0.2);		
	}
	/*
    while(1) {
			//forward
			for (double s=0; s<=1.0;s+=0.05) {
				motorA.forward(s);
				wait(0.3);
			}
			wait(1);
			
			for (double s=1.0; s>=0;s-=0.05) {
				motorA.forward(s);
				wait(0.3);
			}
			wait(1);
			
			//backword
			for (double s=0; s<=1.0;s+=0.05) {
				motorA.backword(s);
				wait(0.3);
			}
			wait(1);
			
			for (double s=1.0; s>=0;s-=0.05) {
				motorA.backword(s);
				wait(0.3);
			}
			wait(1);
    }
		*/
}
