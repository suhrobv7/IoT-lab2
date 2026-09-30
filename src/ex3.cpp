


#include "Arduino.h"

const uint8_t LIGHT_SENSOR_PIN = 33;
const unsigned long CHECK_INTERVAL_MS = 300;
const int LIGHT_ALERT_ON_THRESHOLD = 3000;
const int LIGHT_ALERT_OFF_THRESHOLD = 2500;
unsigned long lastReadTime = 0;
bool lightAlertEnabled = false;

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
	if (now - lastReadTime < CHECK_INTERVAL_MS) {
		return;
	}
	lastReadTime = now;

	const int reading = analogRead(LIGHT_SENSOR_PIN);
	if (!lightAlertEnabled && reading > LIGHT_ALERT_ON_THRESHOLD) {
		lightAlertEnabled = true;
		Serial.println("ALERT=1");
	} else if (lightAlertEnabled && reading < LIGHT_ALERT_OFF_THRESHOLD) {
		lightAlertEnabled = false;
		Serial.println("ALERT=0");
	}
}
