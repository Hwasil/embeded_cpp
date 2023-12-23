#include "mbed.h"

#define BUZZER_PIN PC_9
#define RED_LED_PIN PA_4

//DigitalOut buzzer(BUZZER_PIN);
PwmOut buzzer(BUZZER_PIN);
DigitalOut redLed(RED_LED_PIN);

#define C_NOTE_HALF_PEREIOD 1915 // usec

#define NOTE_c	0
#define NOTE_d	1
#define NOTE_e	2
#define NOTE_f	3
#define NOTE_g	4
#define NOTE_a	5
#define NOTE_b	6
#define NOTE_C	7

int note_preiods[] = {
	3830, 3400, 3038, 2864, 2550, 2272, 2028, 1912
};

int melody[] = {
	NOTE_c, NOTE_c, NOTE_g, NOTE_g, NOTE_a, NOTE_a, NOTE_g //NOTE_f, NOTE_f, NOTE_e, NOTE_e, NOTE_d, NOTE_d, NOTE_c
	//NOTE_e, NOTE_d, NOTE_c, NOTE_d, NOTE_e, NOTE_e, NOTE_e, NOTE_d, NOTE_d, NOTE_d, NOTE_e, NOTE_e, NOTE_e, NOTE_e, NOTE_d, NOTE_c, NOTE_d, NOTE_e, NOTE_e, NOTE_e, NOTE_d, NOTE_d, NOTE_e, NOTE_d, NOTE_c 
};

void playTone(int tone) {
	buzzer.period_us(note_preiods[tone]);
	buzzer = 0.5;
}

void setup() {
	buzzer.period_us(C_NOTE_HALF_PEREIOD * 2);
	buzzer = 0; 
}

int main() {
		int cnt = sizeof(melody) / sizeof(melody[0]); // melody byte
		setup();
	
    while(1) {
			
			for (int i=0; i<cnt; i++) {
				playTone(melody[i]);
				wait_ms(500);
			}
			
			buzzer = 0;
			wait(2.0);
    };	
}
