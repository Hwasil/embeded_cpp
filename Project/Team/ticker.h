#ifndef TICKER_H
#define TICKER_H

#include "mbed.h"

#define GREEN_LED_PIN	PA_13
#define YELLOW_LED_PIN PB_10
#define RED_LED_PIN	PA_4

DigitalOut greenLed(GREEN_LED_PIN);
DigitalOut yellowLed(YELLOW_LED_PIN);
DigitalOut redLed(RED_LED_PIN);

Ticker jsTicker;
Ticker doorTicker;
Ticker yellowLedTicker;

void yellowTk() {
	yellowLed = 0;
}

#endif
