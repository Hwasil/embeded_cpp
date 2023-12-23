#include "mbed.h"
#include "DHT22.h"

#define DHT22_SDA_PIN PB_2

DHT22 dht22(DHT22_SDA_PIN);

void setup() {
	printf("Start DHT22 device test...\n");
}

int main() {
		float temp, humidity;
		setup();
	
    while(1) {
			if (dht22.sample()) {
				temp = dht22.getTemperature() / 10.0;
				humidity = dht22.getHumidity() / 10.0;
				
				printf("Temp = %+4.1f C\t\t Humidity = %4.1f %% \n", temp, humidity);
			}
			
			wait(0.5);
		}
}
