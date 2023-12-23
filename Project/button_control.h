#ifndef	BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include "mbed.h"

#define FIRST_BTN_PIN   PA_14
#define SECOND_BTN_PIN	PB_7
#define THIRD_BTN_PIN		PC_4

#define BUZZER_PIN			PC_9

#define C_NOTE_HALF_PERIOD 	1915		//usec

#define NOTE_c		0
#define NOTE_e		1
#define NOTE_g		2
#define NOTE_b		3

DigitalIn btn1(FIRST_BTN_PIN);
DigitalIn btn2(SECOND_BTN_PIN); 
DigitalIn btn3(THIRD_BTN_PIN);

PwmOut buzzer(BUZZER_PIN);

int note_periods[] = {3830, 3038, 2550, 2028};

int corrmelody[] = {NOTE_c, NOTE_e, NOTE_g, NOTE_c};
int incorrmelody[] = {NOTE_b, NOTE_b, NOTE_b, NOTE_b};

typedef enum {
	NO_EDGE=0, RISING_EDGE, FALLING_EDGE
} edge_t;

#define BTN1_PRESSED() (detectBtn1Edge() == FALLING_EDGE)

edge_t detectBtn1Edge() {
	static int prevState = 1;
	edge_t edge = NO_EDGE;
	
	int currState = btn1;
	if (currState != prevState) {
		wait_ms(50);		// debouncing delay  50ms
		currState = btn1;
		if (currState != prevState) {
			if (currState == 1) edge = RISING_EDGE;
			else edge = FALLING_EDGE;
			prevState = currState;
		}
	}
	
	return edge;
}

#define BTN2_PRESSED() (detectBtn2Edge() == FALLING_EDGE)

edge_t detectBtn2Edge() {
	static int prevState = 1;
	edge_t edge = NO_EDGE;
	
	int currState = btn2;
	if (currState != prevState) {
		wait_ms(50);		// debouncing delay  50ms
		currState = btn2;
		if (currState != prevState) {
			if (currState == 1) edge = RISING_EDGE;
			else edge = FALLING_EDGE;
			prevState = currState;
		}
	}
	
	return edge;
}

#define BTN3_PRESSED() (detectBtn3Edge() == FALLING_EDGE)

edge_t detectBtn3Edge() {
	static int prevState = 1;
	edge_t edge = NO_EDGE;
	
	int currState = btn3;
	if (currState != prevState) {
		wait_ms(50);		// debouncing delay  50ms
		currState = btn3;
		if (currState != prevState) {
			if (currState == 1) edge = RISING_EDGE;
			else edge = FALLING_EDGE;
			prevState = currState;
		}
	}
	
	return edge;
}

void playTone(int tone) {
	buzzer.period_us(note_periods[tone]);
	buzzer = 0.5;
}

#endif
