#include <ctype.h>
#include "mbed.h"

#define GREEN_LED_PIN 	PA_13
#define YELLOW_LED_PIN 	PB_10
#define RED_LED_PIN 		PA_4

DigitalOut greenLed(GREEN_LED_PIN); 
DigitalOut yellowLed(YELLOW_LED_PIN);
DigitalOut redLed(RED_LED_PIN);

#define BT_TX_PIN PA_11
#define BT_RX_PIN PA_12

Serial pc(USBTX, USBRX, 9600);
Serial bt(BT_TX_PIN, BT_RX_PIN, 9600);

void bypass() {
	while (pc.readable() ) {
		bt.putc(pc.getc());
		//pc.putc(pc.getc()); 
	}
	
	while (bt.readable() ) {
		pc.putc(bt.getc());
	}
}
char replyMsg[100];
void controlLeds(int led, bool on) {
	if (led == 1) {
		greenLed = (on = true) ? 1 : 0;
	} 
	else if (led == 2) {
		yellowLed = (on = true) ? 1 : 0;
	} 
	else if (led == 3) {
		redLed = (on = true) ? 1 : 0;
	}
	sprintf(replyMsg, "LED%d is %s\n", led, (on? "on": "off")); // string print

}

bool parseCommand(char* cmd) { // Token :
	//check if '=' char is contained in command
	char* cp = cmd;
	int index = 0;
	while (*cp != '\0') {
		if (*cp == '=') break;
		++cp;
		++index;
	}
	if (*cp != '=') return false;
	
	if (strncmp(cmd, "LED", 3) != 0)
		return false;
	
	int led = cmd[index - 1] - 0x30;
	bool on = true;
	 if (strncmp(&cmd[index+1], "OFF", 3) == 0) {
		 on = false;
	 }
	 
	 controlLeds(led, on);
}

int main() {
		char buf[32];
		char *bp = buf; // start address
	
    while(1) {
       //bypass();
			while (bt.readable()) {
				char c = bt.getc();
				if (c == '\r' || c == ' ') continue;
				else if (c == '\n') {
					*bp = '\0';
					if (parseCommand(buf)) {
						bt.printf("%s", replyMsg);
					}
					bp = buf;
				} 
				else {
					*bp++ = toupper(c);
				}
			}
    }
}


