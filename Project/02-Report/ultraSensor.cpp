#include "mbed.h¡°

#define URF_TRIG_PIN PB_6
#define URF_ECHO_PIN PA_8

#define BUZZER_PIN PC_9
#define RED_LED_PIN PA_4

#define IR_SENSOR_PIN PC_5
#define ALPHA 0.15

Serial pc(USBTX, USBRX, 9600);
DigitalOut urfTrig(URF_TRIG_PIN);
DigitalIn urfEcho(URF_ECHO_PIN);

PwmOut buzzer(BUZZER_PIN);
DigitalOut redLed(RED_LED_PIN);

AnalogIn irSensor(IR_SENSOR_PIN);

int pulseLength; // usec
float dist;      // cm

#define TRNSFORM_CONSTANT 0.01724  
#define C_NOTE_HALF_PEREIOD 1915 // usec

double LPF(double meas) {
	static double prevValue = -1;
	double value = 0;

	if (prevValue < 0) {
		prevValue = meas;
	}
	value = (1.0 - ALPHA) * prevValue + ALPHA * meas;
	prevValue = meas;

	return value;
}

void setup() {
	urfTrig = 0;
	buzzer.period_us(C_NOTE_HALF_PEREIOD * 2);
	buzzer = 0.5; // 50% rate
	pc.printf("--- Distance Sensor ---\n");
}

int main() {
	setup();
	double distance = 0;
	double volt = 0;

	while (1) {
		// sound
		if (buzzerTm.read_ms() >= 1000) {
			buzzer = buzzer.read() == 0 ? 0.5 : 0;
			buzzerTm.reset();
		}

		// send TRIG signal to SRF-04
		urfTrig = 1;
		wait_us(40); // microsecond
		urfTrig = 0;

		// wait for echo signal to be high
		while (!urfEcho);

		// measure pulse length of ECHO signal
		tmr1.reset();
		while (urfEcho);
		pulseLength = tmr1.read_us();
		dist = pulseLength / 58.0; //ultrasonic moving 1s = 85cm?

		// output pulse length and distance to PC
		pc.printf("Pulse length = %d usec\n", pulseLength);
		pc.printf("Distance = %4.1f cm\n\n", dist);

		wait(1.0);

		volt = LPF(irSensor.read());

		if (0.18 <= volt && volt <= 0.9) {
			distance = 26.663 * pow((volt * 3.3), -1.25);
			pc.printf("Distance = %5.2f cm\n", distance);
		}
		else {
			pc.printf("-------cm\n");
		}
		wait(0.3);
	}

}