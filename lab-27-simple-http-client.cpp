#include "mbed.h"
#include "ESP8266.h"

Serial pc(USBTX, USBRX, 115200);

ESP8266 wifi(PA_9, PA_10, 115200);

char SSID[] = "silla04";
char PASSWD[] = "SILLA123";

char resp[1024]; // 1K
char http_cmd[300], comm[300];
int timeout = 8000; // 8 minute

char SERVER_IP[] = "172.17.6.51"; // mobisys.silla.ac.kr
int SERVICE_PORT = 80;
char URL[] = "/yjkim";

void initialized_wifi() {
	pc.printf("*******Resetting wifi module**********\r\n");
	wifi.Reset();
	wait(3.0);
	
	wifi.Reset();
	if (wifi.RcvReply(resp, 5000))
		pc.printf("%s", resp);
	else
		pc.printf("NO response");
	
	pc.printf("************* Setting station mode of wifi wich AP ********\r\n");
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

void send_http_request() {
	pc.printf("******** Make TCP connection to server ********\r\n");
    wifi.startTCPConn(SERVER_IP, SERVICE_PORT);   
    if (wifi.RcvReply(resp, timeout))    
        pc.printf("%s",resp);    
    else
        pc.printf("No response \r\n");
    
	sprintf(http_cmd, "%s", URL);
	pc.printf(">>> Send request URI : %s\r\n", http_cmd);
	
	wifi.sendURL(SERVER_IP, comm);   
    if (wifi.RcvReply(resp, 10000))    
        pc.printf("%s",resp);    
    else
        pc.printf("No response \r\n");		
}
	
void setup() {
	initialized_wifi();
}

int main() {
		setup();
	
		send_http_request();
	
    while(1) {
       wait(1.0); // 1 sec
    }
		
}
