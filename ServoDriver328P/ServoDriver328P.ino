#include <Servo.h>
#include "LED4D7SDisplay.h"
#include "ClickLowButton.h"

#define SERVO_PIN A0
#define CHANGE_INC 100
#define MIN_US 500
#define MAX_US 2500

const byte digit_pins[] = {A4, 11, 12, 13};
const byte segment_pins[] = {2, 3, 4, 5, 6, 7, 8, A5};

LED4D7SDisplay display(digit_pins, segment_pins);

ClickLowButton up_button(10);
ClickLowButton down_button(9);

Servo servo;

unsigned int us = 0;
unsigned long end_pulse = 0;
unsigned long end_period = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\nInitializing...");
  display.setup();
  up_button.setup();
  down_button.setup();
  servo.attach(SERVO_PIN);
  
  servo.write(0);
  delay(500);
  Serial.print("0 degrees is "); Serial.print(servo.readMicroseconds()); Serial.println("μs");
  servo.write(90);
  delay(500);
  Serial.print("90 degrees is "); Serial.print(servo.readMicroseconds()); Serial.println("μs");
  servo.write(180);
  delay(500);
  Serial.print("180 degrees is "); Serial.print(servo.readMicroseconds()); Serial.println("μs");

  servo.detach();
  delay(500);
  servo.attach(SERVO_PIN);
}

void loop() {
  if (us > 0) {
    servo.writeMicroseconds(us);
  }
  if (handle_buttons()) {
    if (us > 0) {
      display.update(us);
    } else {
      display.clear();
    }
  } else {
    display.refresh();
  }
}

bool handle_buttons() {
  bool changed = false;
  bool dbp = down_button.isPressed();
  bool ubp = up_button.isPressed();

  if (dbp && ubp) { // reset to zero when both buttons pressed
    Serial.println("Both buttons pressed -- reset");
    us = 0;
    changed = true;
  } 
  else if (dbp) {
    Serial.println("Down button pressed");
    if (us > MIN_US) {      
      us -= CHANGE_INC;
      changed = true;
    } 
    else if (us > 0) {
      us = 0;
      changed = true;
    }
  } 
  else if (ubp) {
    Serial.println("Up button pressed");
    if (us < MAX_US) {
      if (us > 0) {
        us += CHANGE_INC;
      } else {
        us = MIN_US;
      }
      changed = true;
    }
  }
  
  if (changed) {
    Serial.print("Changed us to ");
    Serial.print(us);
    Serial.println("μs");
  }
  return changed;
}
