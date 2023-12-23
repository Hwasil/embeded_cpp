#ifndef _LIGHT_CONTROL_H_
#define _LIGHT_CONTROL_H_

#include "mbed.h"

typedef enum { GREEN=0x04, YELLOW=0x02, RED=0x01 } light_color_t;

BusOut lightA(PA_4, PB_10, PA_13);
BusOut lightB(PA_1, PB_0, PC_6); // RGB Led / red, blue, green
#define LIGHT_B_YELLOW  0x05

void controlLightA(light_color_t color) {
	lightA = color;
}

void controlLightB(light_color_t color) {
	if (color == YELLOW)
		lightB = LIGHT_B_YELLOW;
	else
		lightB = color;
}

#endif //_LIGHT_CONTROL_H_