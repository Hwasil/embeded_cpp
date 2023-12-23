#include "mbed.h"

#define BT_TX_PIN PA_11
#define BT_RX_PIN PA_12

Serial pc(USBTX, USBRX, 9600);
Serial bt(BT_TX_PIN, BT_RX_PIN, 9600);

DigitalOut myled(LED1);

void bypass() {
	while (pc.readable() ) {
		bt.putc(pc.getc());
		//pc.putc(pc.getc()); 
	}
	
	while (bt.readable() ) {
		pc.putc(bt.getc());
	}
}

int main() {
		
    while(1) {
       bypass();
    }
}


