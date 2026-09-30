


#include "Arduino.h"

const uint8_t BUTTON_PIN = 25;
const uint8_t LED_PINS[] = {26, 27, 12, 14};
const uint8_t DEBOUNCE_INTERVAL_MS = 30;
const uint8_t PRESS_COUNT_LIMIT = 5;
uint8_t pressCount = 0;
int lastButtonReading = LOW;
int stableButtonState = LOW;
unsigned long lastDebounceTime = 0;

/****************************************************/
void setup(void) 
{
	Serial.begin(115200);
	pinMode(BUTTON_PIN, INPUT);
	for (uint8_t pin : LED_PINS) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
}


/****************************************************/
void loop(void) 
{
	const int buttonReading = digitalRead(BUTTON_PIN);
	if (buttonReading != lastButtonReading) {
		lastDebounceTime = millis();
		lastButtonReading = buttonReading;
	}

	if (millis() - lastDebounceTime >= DEBOUNCE_INTERVAL_MS &&
		buttonReading != stableButtonState) {
		stableButtonState = buttonReading;
		if (stableButtonState == HIGH) {
			pressCount = (pressCount + 1) % PRESS_COUNT_LIMIT;
			Serial.print("count=");
			Serial.println(pressCount);

			for (uint8_t index = 0; index < 4; ++index) {
				digitalWrite(LED_PINS[index], index < pressCount ? HIGH : LOW);
			}
		}
	}
}
