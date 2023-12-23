#include "mbed.h"

#if 0
DigitalOut greenLed(PA_13);
DigitalOut yellowLed(PB_10);
DigitalOut redLed(PA_4);

Thread t1,t2;

class BlinkLed {
	public :
		BlinkLed(DigitalOut *o, int p) : led(o), period(p)
		{}
			
			DigitalOut *led;
			int period;
};

void blinkYellowLed() {
	yellowLed = !yellowLed;
	printf("Yellow LED - %s (thread ID : %p)\n", yellowLed ? "ON" : "OFF", ThisThread::get_id());
	
	ThisThread::sleep_for(1000);
}

void blinkRedLed() {
	redLed = !redLed;
	printf("Red LED - %s (thread ID : %p)\n", redLed ? "ON" : "OFF", ThisThread::get_id());
	
	ThisThread::sleep_for(2000);
}

void setup(){
	//t1.start(blinkYellowLed);
	//t2.start(blinkRedLed);
	t1.start(callback(blinkLed, new BlinkLed(&yellowLed, 1000)));
	t2.start(callback(blinkLed, new BlinkLed(&redLed, 2000)));
}

void blinkLed(DigitalOut *led, int period) {
	*led = !*led;
	printf("LED - %s (thread ID : %p)\n", 
	redLed ? "ON" : "OFF", 
	ThisThread::get_id());
	
	ThisThread::sleep_for(period);
}

int main()
{
#ifdef MBED_MAJOR_VERSION
  printf("Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif
	setup();
	/*
	while (1) {
		greenLed = !greenLed;
		ThisThread::sleep_for(500);
		printf("Greeen LED - %s (thread iD: %p)\n", greenLed ? "ON" : "OFF", ThisThread::get_id());		
		
		ThisThread::sleep_for(500);
	}*/
	
	blinkLed(new BlinkLed(&greenLed, 500));
}
#endif

#include "mbed.h"
#include "mbed_events.h"

DigitalOut led1(PA_13); //green Led
InterruptIn sw(PA_14); // the first button

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void rise_handler(void)
{
	queue.call(printf, "rise_handler is contract %p\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}

void fall_handler(void)
{
    printf("fall_handler in context %p\r\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}

int main()
{
    // Request the shared queue
    EventQueue *queue = mbed_event_queue();
    printf("Starting in context %p\r\n", ThisThread::get_id());
    // The 'rise' handler will execute in IRQ context
    sw.rise(rise_handler);
    // The 'fall' handler will execute in the context of the shared queue thread
    sw.fall(queue->event(fall_handler));
}
