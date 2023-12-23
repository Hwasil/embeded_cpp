#ifndef _ACCEL_DEV_H_
#define _ACCEL_DEV_H_

#include "mbed.h"

#define SPI_MOST_PIN PB_15
#define SPI_MISO_PIN PB_14
#define SPI_SCL_PIN PB_13
#define ACCEL_CS_PIN PB_12

SPI spiMaster(SPI_MOST_PIN, SPI_MISO_PIN, SPI_SCL_PIN);
DigitalOut csAccel(ACCEL_CS_PIN);

#define SELECT_ACCEL_DEV() csAccel=0  // low active
#define DESELECT_ACCEL_DEV() csAccel=1  

void initSPIMaster() {
	spiMaster.format(8, 3);
	spiMaster.frequency(100000);
	
	DESELECT_ACCEL_DEV();
}

void initAccelDev() {
	SELECT_ACCEL_DEV(); //active
	
	spiMaster.write(0x00 | 0x31); // ( | register address)
	spiMaster.write(0x01); // +-4g
	spiMaster.write(0x00 | 0x2D); 
	spiMaster.write(0x08); // measurment mode
	
	DESELECT_ACCEL_DEV();
}

int getAccelDevID() {
	SELECT_ACCEL_DEV(); 
	
	spiMaster.write(0x80 | 0x00); // (read data| register address)
	int id = spiMaster.write(0x00);  // read ID data
	// for read == dommy data 1byte
	DESELECT_ACCEL_DEV();
	
	return id;
}

void getAccelData(float* accelData) { // 3 
	char buffer[6];
	int16_t data;
	
	SELECT_ACCEL_DEV(); 
	
	spiMaster.write(0x80 | 0x40 | 0x32); // (read multi byte | register address)
	for (int i=0; i<6; i++) {
		buffer[i]=spiMaster.write(0x00);
	}
	DESELECT_ACCEL_DEV();
	
	data = (buffer[1] << 8) | buffer[0]; // make 16bit (x)
	accelData[0]= data * 0.0078;
	data = (buffer[3] << 8) | buffer[2]; // make 16bit (y)
	accelData[1]= data * 0.0078;
	data = (buffer[5] << 8) | buffer[4]; // make 16bit (z)
	accelData[2]= data * 0.0078;
}

#endif