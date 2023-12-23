#include "mbed.h"

#define BYPASS_MODE

Serial pc(USBTX,USBRX, 115200);
Serial wifi(PA_9, PA_10, 115200);

DigitalOut myled(LED1);

Timer t;
#define WIFI_RECEIVE_TIMEOUT 5.0 // 

void sendCmd(char*, int);
void receiveReply();
void initializeWifi();

#ifdef BYPASS_MODE

void bypass() {
	while (pc.readable()) {
		wifi.putc(pc.getc());
	}
	
	while (wifi.readable()) {
		pc.putc(wifi.getc());	
	}
}

#endif

void setup() {
	t.start();
}

int main() {
#ifndef BYPASS_MODE
		setup();
		
		initializeWifi();
#endif
	
    while(1) {
#ifdef BYPASS_MODE
			bypass();
#else 
			wait(1.0);
#endif
    }
		
}

void sendCMD(char * cmd, int len) {
		char *cp = cmd;
		if (len <= 0) {
			while (*cp != '\0') {
				wifi.putc(*cp++);
			}
		} else {
			for (int i=0 ; i<len; i++) {
				wifi.putc(*cp++);
			}
		}
}


void receiveReply() {
	char buf[100];
	char *cp = buf;
	char ch;
	bool ok = false;
	
	t.reset();
	
	while ((t.read() < WIFI_RECEIVE_TIMEOUT) && !ok ) {
		if (wifi.readable()) {
			ch = wifi.getc();
			if (ch != '\n') {
				*cp++ = ch;
			} 
			else {
				*cp++ = '\0';
				if (strncmp(buf, "OK", 2) == 0 || strncmp(buf, "ready", 5) == 0) {
					ok = true;
				}
				pc.printf("%s\n", buf);
				cp = buf;
			}
		}
	}
	
	if (!ok) {
		pc.printf("Timeout is waiting for reply...\n");
	} 
}

void initializeWifi() {
	sendCMD((char *)"AT\r\n", 0);
	receiveReply();	
	sendCMD((char *)"AT\r\n", 0);
	receiveReply();
	sendCMD((char *)"AT+GMR\r\n", 0);
	receiveReply();
}
