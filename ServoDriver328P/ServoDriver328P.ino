
#include "LED4D7SDisplay.h"
#include "ClickLowButton.h"

// Digit Pins
#define D1 A4
#define D2 11
#define D3 12
#define D4 13

// Segment Pins
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define P A5

const byte digit_pins[] = {D1, D2, D3, D4};
const byte segment_pins[] = {A, B, C, D, E, F, G, P};
LED4D7SDisplay display(digit_pins, segment_pins);
ClickLowButton up_button(10);
ClickLowButton down_button(9);
byte sel_digit = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\nInitializing...");
  
  display.setup();
  up_button.setup();
  down_button.setup();
}

void loop() {
  if (down_button.isPressed()) {
    Serial.println("Down button pressed");
    sel_digit--;
    if (sel_digit < 0) sel_digit = NUM_DIGITS;
    // TODO: update display
  } else if (up_button.isPressed()) {
    Serial.println("Up button pressed");
    sel_digit++;
    if (sel_digit > NUM_DIGITS) sel_digit = 0;
    // TODO: update display
  }
}
