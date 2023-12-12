
#include "LED4D7SDisplay.h"
#include "ClickLowButton.h"


const byte digit_pins[] = {A4, 11, 12, 13};
const byte segment_pins[] = {2, 3, 4, 5, 6, 7, 8, A5};

LED4D7SDisplay display(digit_pins, segment_pins);

ClickLowButton up_button(10);
ClickLowButton down_button(9);

#define PPM_PIN A0
#define CHANGE_INC 100
#define MIN_DUR 0
#define MAX_DUR 9900

unsigned int pulse_duration = 0;
unsigned long end_pulse = 0;
unsigned long end_period = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\nInitializing...");
  display.setup();
  up_button.setup();
  down_button.setup();
}

void loop() {
  pulse_period();
  if (handle_buttons()) {
    display.update(pulse_duration);
  } else {
    display.refresh();
  }
}

bool handle_buttons() {
  bool changed = false;
  bool dbp = down_button.isPressed();
  bool ubp = up_button.isPressed();

  if (dbp && ubp) { // reset to zero when both buttons pressed
    pulse_duration = MIN_DUR;
    changed = true;
  } 
  else if (dbp && pulse_duration > MIN_DUR) {
    pulse_duration -= CHANGE_INC;
    changed = true;
  } 
  else if (ubp && pulse_duration < MAX_DUR) {
    pulse_duration + CHANGE_INC;
    changed = true;
  }

  return changed;
}

void pulse_period() {
  if (pulse_duration > 0) {
    if (micros() > end_pulse) {
      digitalWrite(PPM_PIN, LOW);
    }
    if (millis() > end_period) {
      begin_new_period();
    }
  } 
  else {
    digitalWrite(PPM_PIN, LOW);
  }
}

void begin_new_period() {
  if (pulse_duration > 0) {
    end_pulse = micros() + pulse_duration;
    digitalWrite(PPM_PIN, HIGH);
  } else {
    digitalWrite(PPM_PIN, LOW);
  }
  end_period = millis() + 20;
}

