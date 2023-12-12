#include "ClickLowButton.h"

ClickLowButton::ClickLowButton(const byte p): pin(p), last_reading(HIGH), last_state(HIGH), last_debounce_time(0) {}

void ClickLowButton::setup() {
  pinMode(pin, INPUT_PULLUP);
}

bool ClickLowButton::isPressed() {
  int reading = digitalRead(pin);
  if (reading != last_reading) {
    last_debounce_time = millis();
  }
  last_reading = reading;
  if ((millis() - last_debounce_time) > DEBOUNCE_DELAY) {
    if (last_state != reading) {
      last_state = reading;
      return (reading == LOW);
    }
  }
  return false;
}
