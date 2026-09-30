


#include "Arduino.h"

const uint8_t LIGHT_SENSOR_PIN = 33;
const unsigned long SAMPLE_INTERVAL_MS = 1000;
const uint8_t SAMPLE_COUNT = 10;
unsigned long lastSampleTime = 0;

/****************************************************/
void setup(void) 
{
	Serial.begin(115200);
	pinMode(LIGHT_SENSOR_PIN, INPUT);
}


/****************************************************/
void loop(void) 
{
	const unsigned long now = millis();
	if (now - lastSampleTime < SAMPLE_INTERVAL_MS) {
		return;
	}
	lastSampleTime = now;

	int minimum = 4095;
	int maximum = 0;
	long sum = 0;

	for (uint8_t sample = 0; sample < SAMPLE_COUNT; ++sample) {
		const int reading = analogRead(LIGHT_SENSOR_PIN);
		if (reading < minimum) minimum = reading;
		if (reading > maximum) maximum = reading;
		sum += reading;
	}

	Serial.print("min=");
	Serial.print(minimum);
	Serial.print(" max=");
	Serial.print(maximum);
	Serial.print(" avg=");
	Serial.println(sum / SAMPLE_COUNT);
}
