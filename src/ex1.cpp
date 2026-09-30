#include "Arduino.h"

const uint8_t LED_PINS[] = {26, 27, 12, 14, 12, 27};
const char *LED_NAMES[] = {"RED", "GREEN", "YELLOW", "BLUE", "YELLOW", "GREEN"};
const uint8_t STEP_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);
const unsigned long CHASE_DELAY_MS = 150;
uint8_t currentStep = 0;

/****************************************************/
void setup(void) 
{
    Serial.begin(115200);
    for (uint8_t pin : LED_PINS) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}


/****************************************************/
void loop(void) 
{
    for (uint8_t pin : LED_PINS) {
        digitalWrite(pin, LOW);
    }

    digitalWrite(LED_PINS[currentStep], HIGH);
    Serial.print("chase=");
    Serial.println(LED_NAMES[currentStep]);
    delay(CHASE_DELAY_MS);

    currentStep = (currentStep + 1) % STEP_COUNT;
}
