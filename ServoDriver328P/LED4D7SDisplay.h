#ifndef SevenSegmentDisplay_H
#define SevenSegmentDisplay_H

#include <Arduino.h>

#define NUM_DIGITS 4
#define NUM_SEGMENTS 8
#define MAX_VALUE 9999

class LED4D7SDisplay {
  
  byte digit_pins[NUM_DIGITS];
  byte segment_pins[NUM_SEGMENTS];
  byte digit_values[NUM_DIGITS];

  public:
    LED4D7SDisplay(const byte dp[NUM_DIGITS], const byte sp[NUM_SEGMENTS]);
    ~LED4D7SDisplay();

    void setup();                           // call this in the main setup function
    void clear();
    void refresh();                         // should be called in every loop
    void update(const unsigned int value);  // value must be 4 digits or less

  private:
    void displayDigit(const byte digit, const byte value_index);
};

#endif // SevenSegmentDisplay_H
