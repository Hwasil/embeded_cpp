#include "mbed.h"
#include "Adafruit_GFX/Adafruit_SSD1306.h"


I2C i2cMaster(I2C_SDA, I2C_SCL);  //D14, 15D
Adafruit_SSD1306_I2c myOled(i2cMaster, D13, 0x78, 64, 128);

void setup() {
	i2cMaster.frequency(400000); // default
}

int main() {
	int cnt = 0;
	bool inverted = false;
	int textSize = 1;
	
	setup();
	
	wait(2.0);
	myOled.clearDisplay(); 							// Delete display buffer
	
	myOled.setTextSize(textSize);
	myOled.printf("%ux%u OLED Display\r\n", myOled.width(), myOled.height());
	myOled.display();
		
  while(1) {
		myOled.drawRect(40, 10, 40, 50, WHITE);
	
		myOled.setTextSize(4);
		if (++cnt > 9) cnt=0;
		
		myOled.setTextCursor(44, 14); 		// cursor position
		myOled.writeChar(0x30 + cnt); 		// change askii
		myOled.display();
		
		
/*		if (++cnt % 5 == 0) {
			inverted = !inverted;
			myOled.invertDisplay(inverted);
			if (++textSize > 7) textSize = 1;
			myOled.setTextSize(textSize);
		}
		
		myOled.printf("%u\r", cnt);
		myOled.display();
*/				
		wait(1.0); 

  }
		
}
