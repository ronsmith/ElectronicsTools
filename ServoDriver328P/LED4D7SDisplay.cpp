#include "LED4D7SDisplay.h"

#define LED_ON_DUR 100

#define NO_VAL 10
#define E_VAL  11
#define F_VAL  12
#define r_VAL  13

byte value_segs[][8] = {
  // A     B     C     D     E     F     G     *
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW,  LOW}, // 0
  { LOW, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW}, // 1
  {HIGH, HIGH,  LOW, HIGH, HIGH,  LOW, HIGH,  LOW}, // 2
  {HIGH, HIGH, HIGH, HIGH,  LOW,  LOW, HIGH,  LOW}, // 3
  { LOW, HIGH, HIGH,  LOW,  LOW, HIGH, HIGH,  LOW}, // 4
  {HIGH, LOW,  HIGH, HIGH,  LOW, HIGH, HIGH,  LOW}, // 5
  {HIGH, LOW,  HIGH, HIGH, HIGH, HIGH, HIGH,  LOW}, // 6
  {HIGH, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW}, // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW}, // 8
  {HIGH, HIGH, HIGH, HIGH,  LOW, HIGH, HIGH,  LOW}, // 9
  { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW}, // NO_VAL
  {HIGH,  LOW,  LOW, HIGH, HIGH, HIGH, HIGH,  LOW}, // E_VAL
  {HIGH,  LOW,  LOW,  LOW, HIGH, HIGH, HIGH,  LOW}, // F_VAL
  { LOW,  LOW,  LOW,  LOW, HIGH,  LOW, HIGH,  LOW}  // r_VAL
};

const byte MAX_VALUE_INDEX = sizeof(value_segs) / sizeof(value_segs[0]);

LED4D7SDisplay::LED4D7SDisplay(const byte dp[NUM_DIGITS], const byte sp[NUM_SEGMENTS]) {
  for (int d = 0; d < NUM_DIGITS; d++) {
    digit_pins[d] = dp[d];
    digit_values[d] = NO_VAL;  
  }
  for (int s = 0; s < NUM_SEGMENTS; s++) {
    segment_pins[s] = sp[s];
  }
}

LED4D7SDisplay::~LED4D7SDisplay() {
  clear();
}

void LED4D7SDisplay::setup() {
  for (int d = 0; d < NUM_DIGITS; d++) {
    pinMode(digit_pins[d], OUTPUT);
    digitalWrite(digit_pins[d], HIGH);
  }
  for (int s = 0; s < NUM_SEGMENTS; s++) {
    pinMode(segment_pins[s], OUTPUT);
    digitalWrite(segment_pins[s], LOW);
  }
}

void LED4D7SDisplay::clear() {
  if (Serial) Serial.println("Clearing display");
  for (int d = 0; d < NUM_DIGITS; d++) {
    digit_values[d] = NO_VAL;
  }
  refresh();
}

void LED4D7SDisplay::refresh() {
  for (int d = 0; d < NUM_DIGITS; d++) {
    displayDigit(d, digit_values[d]);
  }
}

void LED4D7SDisplay::update(const unsigned int value) {
  if (value <= MAX_VALUE) {
    unsigned int v1000 = value / 1000;
    unsigned int v100 = (value / 100) - (v1000 * 10);
    unsigned int v10 = (value / 10) - (v1000 * 100) - (v100 * 10);
    unsigned int v1 = value - (v1000 * 1000) - (v100 * 100) - (v10 * 10);
    digit_values[0] = value > 999 ? v1000 : NO_VAL;
    digit_values[1] = value > 99 ? v100 : NO_VAL;
    digit_values[2] = value > 9 ? v10 : NO_VAL;
    digit_values[3] = v1;
  } else {
    digit_values[0] = E_VAL;
    digit_values[1] = r_VAL;
    digit_values[2] = r_VAL;
    digit_values[3] = NO_VAL;
  }
  refresh();
}

void LED4D7SDisplay::displayDigit(const byte digit, const byte value_index) {
  for (int s = 0; s < NUM_SEGMENTS; s++) {
    digitalWrite(segment_pins[s], value_segs[value_index][s]);
  }
  digitalWrite(digit_pins[digit-1], LOW);
  delay(LED_ON_DUR);
  digitalWrite(digit_pins[digit-1], HIGH);
  for (int s = 0; s < NUM_SEGMENTS; s++) {
    digitalWrite(segment_pins[s], LOW);
  }
}
