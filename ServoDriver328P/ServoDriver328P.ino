#include <SevSeg.h>

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

const byte num_digits = 4;
const byte num_segments = 7+1;

byte digit_pin[] = {D1, D2, D3, D4};
byte segment_pin[] = {A, B, C, D, E, F, G, P};

// Buttons
#define DOWN 0
#define UP 1

byte button_pin[] = {9, 10};
byte last_reading[] = {HIGH, HIGH};
byte last_state[] = {HIGH, HIGH};
unsigned long last_debounce_time[] = {0, 0};
unsigned long debounce_delay = 50;
byte sel_digit = 0;

#define E_SEGS 10
#define F_SEGS 11
#define r_SEGS 12

bool num_segs[][8] = {
  // A      B      C      D      E      F      G      *
  { true,  true,  true,  true,  true,  true, false, false}, // 0
  {false,  true,  true, false, false, false, false, false}, // 1
  { true,  true, false,  true,  true, false,  true, false}, // 2
  { true,  true,  true,  true, false, false,  true, false}, // 3
  {false,  true,  true, false, false,  true,  true, false}, // 4
  { true, false,  true,  true, false,  true,  true, false}, // 5
  { true, false,  true,  true,  true,  true,  true, false}, // 6
  { true,  true,  true, false, false, false, false, false}, // 7
  { true,  true,  true,  true,  true,  true,  true, false}, // 8
  { true,  true,  true,  true, false,  true,  true, false}, // 9
  { true, false, false,  true,  true,  true,  true, false}, // E
  { true, false, false, false,  true,  true,  true, false}, // F
  {false, false, false, false,  true, false,  true, false} // r
};

void setup() {
  Serial.begin(115200);
  Serial.println("\nInitializing...");
  
  for (int s = 0; s < num_segments; s++) {
    pinMode(segment_pin[s], OUTPUT);
  }
  for (int d = 0; d < num_digits; d++) {
    pinMode(digit_pin[d], OUTPUT);
  }

  clear_display();

  pinMode(button_pin[DOWN], INPUT_PULLUP);
  pinMode(button_pin[UP], INPUT_PULLUP);
}


void loop() {
  int bs = buttonPressed(DOWN);
  if (bs) {
    Serial.println("Down button pressed");
    sel_digit--;
    if (sel_digit < 0) sel_digit = num_digits;
    update_display();
  } 
  else {
    bs = buttonPressed(UP);
    if (bs) {
      Serial.println("Up button pressed");
      sel_digit++;
      if (sel_digit > num_digits) sel_digit = 0;
      update_display();
    }
  }
}

bool buttonPressed(int button) {
  int reading = digitalRead(button_pin[button]);
  if (reading != last_reading[button]) {
    last_debounce_time[button] = millis();
  }
  last_reading[button] = reading;
  if ((millis() - last_debounce_time[button]) > debounce_delay) {
    if (last_state[button] != reading) {
      last_state[button] = reading;
      return (reading == LOW);
    }
  }
  return false;
}

void update_display() {
  clear_display();
  
  if (sel_digit > 0) {
    Serial.print("Turning on all segments for Digit "); 
    Serial.println(sel_digit);
    for (int s = 0; s < num_segments; s++) {
      digitalWrite(segment_pin[s], HIGH);
    }
    digitalWrite(digit_pin[sel_digit-1], LOW);
  }
}

void clear_display() {
  Serial.println("Clearing display");
  for (int d = 0; d < num_digits; d++) {
    digitalWrite(digit_pin[d], HIGH);
  }
  for (int s = 0; s < num_segments; s++) {
    digitalWrite(segment_pin[s], LOW);
  }
}