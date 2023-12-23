#include "mbed.h"

Serial pc(USBTX, USBRX);
int cnt = 0;

void setup() {
	pc.baud(9600); 
}

int main() {
		
    while(1) {
// echo test
//			while (pc.readable()) {
//        pc.putc(pc.getc());
//    }
			
			wait(1.0);
			cnt++;
			pc.printf("Counter = %d\r", cnt);
	}
}
