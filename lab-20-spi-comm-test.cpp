#include "mbed.h"
#include "accel_dev.h"

//Serial pc(USBRX, USBTX, 9600); // ebed API 
float accelData[3];

void setup() {
	initSPIMaster();
	initAccelDev();
	
	printf("Start...\n");
}
int main() {
		setup();
	
	printf("ADXL345 Device ID : 0x%2x \n", getAccelDevID());
	
    while(1) {
        getAccelData(accelData);
			
				printf("X = %+1.2fg\t Y = %+1.2fg\t Z = %+1.2fg\n",
							accelData[0], accelData[1], accelData[2]);
			
			wait(0.3);
    }
		
}
