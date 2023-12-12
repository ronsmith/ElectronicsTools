#ifndef ClickLowButton_H
#define ClickLowButton_H

#include <Arduino.h>

#define DEBOUNCE_DELAY 50

class ClickLowButton {
  
  byte pin;
  byte last_reading;
  byte last_state;
  unsigned long last_debounce_time;

  public:
    ClickLowButton(const byte p);

    void setup();
    bool isPressed();
};

#endif
