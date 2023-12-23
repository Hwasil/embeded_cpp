#include "mbed.h"
#include "ESP8266.h"
#include "DHT22.h"
#include "BMP180.h"

Serial pc(USBTX, USBRX, 115200);
AnalogIn cdsSensor(A0);
DHT22 dht22(PB_2);

I2C i2cMaster(I2C_SDA, I2C_SCL);
BMP180 bmp180(&i2cMaster);

ESP8266 wifi(PA_9, PA_10, 115200);
 
 // AP
char SSID[] = "silla04";
char PASSWD[] = "SILLA123";

char resp[1024]; // 1K
char http_cmd[300], comm[300];
int timeout = 8000; // 8 seconds

char THINGSPEAK_IP[] = "186.106.153.149"; // api.thingspeak.com
int SERVICE_PORT = 80;
char UPDATE_URL[] = "/undate?api_key=%s&field1=%.1f&field2=%.1f&field3=%.1f&field4=%.1f";
char UPDATE_API_KEY[] = "3XX63NZAJBXO8281"; // %s position => It's mine

float brightness;
float temperature;
float humidity;
float altitude;

void getBrightness() {
	float value = 0.0;
	for (int i=0; i<10; i++) {
		value += cdsSensor.read();
		wait_ms(250);
	}
	brightness = (value / 10.0) * 100; // percent
	pc.printf("Brghtness = %.1f %%\n", brightness);
	
}

void getTemperature() {
	if (dht22.sample()) {
		temperature = dht22.getTemperature();
		humidity = dht22.getHumidity() / 10.0;
		pc.printf("Temperature = %.1f C, Humidity = %.1f %% \r\n", temperature, humidity);
	}
}

void getAltitude() {
	float temp;
	int pressure;
	
	bmp180.startTemperature();
	wait_ms(5);
		if (bmp180.getTemperature(&temp) < 0) {
			pc.printf("Fail to get Temperature data... \n");
		}
				
		bmp180.startPressure(BMP180::STANDARD);
		wait_ms(20);
		if (bmp180.getPressure(&pressure) < 0 ) {
			pc.printf("Fail to get Temperature data... \n");
		}
				
		//pc.printf("Temperature = %4.1f C, Pressure = %d hpa \n", temp/10, pressure/10);
				
		altitude =44330.f * (1.0f - pow((pressure/102710.0f), (1.0f/5.255f)));
		pc.printf("Altitude = %.1f M\n\n", altitude);
}

void initialized_wifi() {
	pc.printf("*******Resetting wifi module**********\r\n");
	wifi.Reset();
	wait(3.0);
	
	wifi.Reset();
	// wait for 5 seconds for response, 
	if (wifi.RcvReply(resp, 5000))
		pc.printf("%s", resp);
	else
		pc.printf("NO response");
	
	pc.printf("************* Setting station mode of wifi with AP ********\r\n");
	wifi.SetMode(1);
	if (wifi.RcvReply(resp, timeout))
		pc.printf("%s", resp);
	else
		pc.printf("NO response while setting mode. \r\n");
	
	 pc.printf("******** Get AP list ********\r\n");
    wifi.GetList(resp);  
		pc.printf("%s",resp);	
    
	 pc.printf("******** Joining network with SSID and PASS ********\r\n");
    wifi.Join(SSID, PASSWD);     
    if (wifi.RcvReply(resp, 15000))    
        pc.printf("%s",resp);   
    else
        pc.printf("No response while connecting to network \r\n");
		
		
		pc.printf("******** Getting IP and MAC of module ********\r\n");
			wifi.GetIP(resp); 
			pc.printf("%s",resp);
		
		pc.printf("******** Set WIFI UART Passthrough ********\r\n");
			wifi.setTransparent();     
			if (wifi.RcvReply(resp, timeout))    
					pc.printf("%s",resp);
			else
					pc.printf("No response \r\n");
			
		pc.printf("******** Set single connection mode ********\r\n");
			wifi.SetSingle();     
			if (wifi.RcvReply(resp, timeout))    
					pc.printf("%s",resp);
			else
					pc.printf("No response \r\n");
}

void update_thingspeak_channel() {
	pc.printf("******** Make TCP connection to server ********\r\n");
    wifi.startTCPConn(THINGSPEAK_IP, SERVICE_PORT);   
    if (wifi.RcvReply(resp, timeout))    
        pc.printf("%s",resp);    
    else
        pc.printf("No response \r\n");
  
	// create request URL
	sprintf(http_cmd, UPDATE_URL, UPDATE_API_KEY, 
					temperature, humidity, brightness, altitude);
	pc.printf(">>> Send request URI : %s\r\n", http_cmd);
	
	wifi.sendURL(http_cmd, comm);   
    if (wifi.RcvReply(resp, 10000))    
        pc.printf("%s",resp);    
    else
        pc.printf("No response \r\n");		
}
	
void setup() {
	i2cMaster.frequency(400000);
	initialized_wifi();
}

int main() {
		setup();
	
    while(1) {
			// read sensor data
			getBrightness();
			getTemperature();
			
			// send sensor data to thingspeak.com
			update_thingspeak_channel();
			
      wait(30.0); // 10 sec
    }
		
}
