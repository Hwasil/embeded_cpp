#include "mbed.h"
#include "BMP180.h"

#define I2C_SDA_PIN D14
#define I2C_SCL_PIN D15

//I2C bmp180(I2C_SDA_PIN, I2C_SCL_PIN);
BMP180 bmp180(I2C_SDA_PIN, I2C_SCL_PIN);

DigitalOut myled(LED1);

void setup() {
		//bmp180.frequency(400000);
		bmp180.init();
	printf("BMP180 : 0x%02x \n", bmp180.checkId());
	wait(1.0);
}

#define BMP180_I2C_ADDR 	0xEE // register??
#define REG_ADDR_ID				0xD0 

/*
void getBMP180Id() {
	char addr;
	char data;
	
	addr = REG_ADDR_ID;
	bmp180.write(BMP180_I2C_ADDR, &addr, 1);
	
	bmp180.read(BMP180_I2C_ADDR, &data, 1);
	printf("BMP180 ID : 0x%02x \n", data);
}
*/

int main() {
		int pressure = 0;
		float temp = 0.0;
		float altittude = 0.0;
	
		setup();
	
    while(1) {
        bmp180.startTemperature();
				wait_ms(5);
				if (bmp180.getTemperature(&temp) < 0) {
					printf("Fail to get Temperature data... \n");
				}
				
				bmp180.startPressure(BMP180::STANDARD);
				wait_ms(20);
				if (bmp180.getPressure(&pressure) < 0 ) {
					printf("Fail to get Temperature data... \n");
				}
				
				printf("Temperature = %4.1f C, Pressure = %d hpa \n", temp/10, pressure/10);
				
				altittude =44330.f * (1.0f - pow((pressure/102710.0f), (1.0f/5.255f)));
				printf("Altittude = %.1f M\n\n", altittude);
				
				wait(1.0);
    }
		
}
