#include "mbed.h"
#include "Adafruit_GFX_lib/Adafruit_SSD1306.h"
#include "DHT22.h"
#include "motordrive.h"
#include "button_control.h"
#include "ticker.h"

#define DHT22_SDA_PIN		PB_2

#define JS_X_AXIS PC_2
#define JS_Y_AXIS PC_3
#define MOTOR_A_PWM_PIN D11
#define MOTOR_A_DIR_PIN PC_8

Serial pc(USBTX, USBRX, 115200);
DHT22 dht22(PB_2);

AnalogIn xAxis(JS_X_AXIS);
AnalogIn yAxis(JS_Y_AXIS);

Motor motorA(MOTOR_A_PWM_PIN, MOTOR_A_DIR_PIN);
double speed = 0.5;

typedef enum { NORMAL_MODE=0, DOOR_CTRL_MODE } state_t;
state_t state;

float temperature;
float humidity;
bool lockState;

I2C i2cMaster(I2C_SDA, I2C_SCL);		//D14, D15
Adafruit_SSD1306_I2c myOled(i2cMaster, D13, 0x78, 64, 128);
int textSize;

int password[] = {0, 0, 0, 0};
int inputpw[4];
int position = 0;
int x, y;

#define NEUTRAL_VALUE 71 // mine

void readJoystick() {
	x = xAxis * 100;
	y = yAxis * 100;
	
	x = NEUTRAL_VALUE - x;
	if (abs(x) <= 2) x = 0;
	
	y = NEUTRAL_VALUE - y;
	if (abs(y) <= 2) y = 0;
}

bool entered() {
	lockState = true;
		
		for (int i = 0; i < (sizeof(password)/sizeof(password[0])); i++) {
			if (inputpw[i] != password[i]) {
				lockState = false;
			}
		}
	return lockState;
}

void corrMelody() {
	int cnt = sizeof(corrmelody) / sizeof(corrmelody[0]);
	
	for (int i = 0; i < cnt; i++) {
		playTone(corrmelody[i]);
		wait_ms(300);
	}
	
	buzzer = 0;
}

void incorrMelody() {
	int cnt = sizeof(incorrmelody) / sizeof(incorrmelody[0]);
	
	for (int i = 0; i < cnt; i++) {
		playTone(incorrmelody[i]);
		wait_ms(300);
	}
	
	buzzer = 0;
}

void timeout() {
	motorA.stop();
	lockState = false;
	greenLed = 0;
}


void presState() {
	if (lockState == true) {
		myOled.printf("Door Open!");
		myOled.display();
	} else if (lockState == false) {
		myOled.printf("Door Closed!");
		myOled.display();
	}
}

void getTempHumidity() { //
    if (dht22.sample()) {
			myOled.setTextCursor(0, 0);
			myOled.printf("Temp: %.1f C\nHumidity: %.1f %\nState: ", 
			dht22.getTemperature() / 10.0, dht22.getHumidity() / 10.0);
			presState();
			myOled.display();
			wait(1.0);
			myOled.clearDisplay();
    }
}

void start() {
	myOled.clearDisplay();
	myOled.setTextCursor(0,0);
	myOled.printf("Input Password : %d%d%d%d", inputpw[0], inputpw[1], inputpw[2], inputpw[3]);
	if (y > 0) {
		inputpw[position]++;
		if (inputpw[position] > 9) {
			inputpw[position] = 0;
    }
  } else if (y < 0) {
		inputpw[position]--;
		if (inputpw[position] < 0) {
			inputpw[position] = 9;
    }
  }
	
	if (x < 0) {
		motorA.stop();
		lockState = false;
		greenLed = 0;
  }

  if (BTN2_PRESSED()) {
		position++;
    if (position > 3) {
			position = 0;
		}
		yellowLed = 1;
		yellowLedTicker.attach(&yellowTk, 0.1);
    wait(0.2); // Button debounce delay
	}
	
	if (BTN3_PRESSED()) {
		if (entered() == true) {
			doorTicker.attach(&timeout, 30.0);
			motorA.forward(speed);
			myOled.printf("\nDoor Open!");
			myOled.display();
			greenLed = 1;
			corrMelody();
			wait(2.0);
			
			
		} else if (entered() == false) {
			myOled.printf("\nRetry..");
			myOled.display();
			redLed = 1;
			incorrMelody();
			wait(2.0);
			redLed = 0;
			
		}
	}
	myOled.display();
}

void setup() {
	i2cMaster.frequency(400000);
	wait(1.0);
	myOled.clearDisplay();
	motorA.stop();
	lockState = false;
	
	state = NORMAL_MODE;
	
	buzzer.period_us(C_NOTE_HALF_PERIOD * 2);
	buzzer = 0;
	
	jsTicker.attach(&readJoystick, 0.2);
}

int main() {	
	setup();
	myOled.setTextCursor(0,0);
	textSize = 1;
	myOled.setTextSize(textSize);
	
	while(1) {
		switch (state) {
			case NORMAL_MODE:
				getTempHumidity();
				if (BTN1_PRESSED()) {
					state = DOOR_CTRL_MODE;
				}
				break;
			case DOOR_CTRL_MODE:
				start();
				if (BTN1_PRESSED()) {
					state = NORMAL_MODE;
				}
			default:
			  break;
		}		
  }
		
}
