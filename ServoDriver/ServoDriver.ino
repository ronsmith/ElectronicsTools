#include <Wire.h>
#include <Serial.h>
#include <stdio.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nI2C Scanner");
}

void loop() {
  int num_devices = 0;
  byte error;
  char msg[50];

  Serial.println("\nScanning...");

  for (byte address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      sprintf(msg, "I2C device found at address 0x%X", address);
      num_devices++;
    } else if (error == 4) {
      sprintf(msg, "Unknown error at address 0x%X", address);
    }
    Serial.println(msg);
  }

  if (num_devices == 0) {
    Serial.println("No I2C devices found");
  }
  Serial.println("Done.");
  delay(5000); // wait 5 seconds for the next scan
}

// #include "LCD_I2C.h"
// #include <limits.h>

// unsigned int pulse_duration;
// unsigned int last_displayed;
// unsigned long end_pulse;
// unsigned long end_period;

// LCD_I2C lcd(0x27, 16, 2);

// void setup() {
//   lcd.init();
//   lcd.display();
//   lcd.noCursor();
//   lcd.setCursor(0, 0);
//   lcd.print("Pulse duration");  
// }

// void loop() {

// }

// void setup() {
//   pinMode(PIN_PB3, INPUT_PULLUP);
//   pinMode(PIN_PB4, INPUT_PULLUP);
//   pinMode(PIN_PB1, OUTPUT);
//   digitalWrite(PIN_PB1, LOW);
//   pulse_duration = 0;
//   last_displayed = 1;
//   end_pulse = 0;
//   end_period = 0;
//   lcd.init();
//   lcd.noCursor();
//   lcd.setCursor(0, 0);
//   lcd.print("Pulse duration");
//   display_pulse_duration();
// }

// void loop() {
//   handle_buttons();
//   pulse_period();
//   display_pulse_duration();
// }

// void handle_buttons() {
//   int b1;
//   int b2;

//   b1 = digitalRead(PIN_PB3);
//   b2 = digitalRead(PIN_PB4);
//   if (b1 == LOW && b2 == LOW) { // do a reset to zero
//     pulse_duration = 0;
//   } 
//   else if (b1 == LOW && pulse_duration < 10000) { // increase pulse duration
//     pulse_duration += 100;
//     if (pulse_duration == 100) {
//       begin_new_period();
//     } // else the new value will get picked up when the next period starts
//   } 
//   else if (b2 == LOW && pulse_duration > 0) { // decrease pulse duration
//     pulse_duration -= 100;
//   }
// }

// void pulse_period() {
//   if (pulse_duration > 0) {
//     if (micros() > end_pulse) {
//       digitalWrite(PIN_PB1, LOW);
//     }
//     if (millis() > end_period) {
//       begin_new_period();
//     }
//   } 
//   else {
//     digitalWrite(PIN_PB1, LOW);
//   }
// }

// void begin_new_period() {
//   end_pulse = micros() + pulse_duration;
//   digitalWrite(PIN_PB1, HIGH);
//   end_period = millis() + 20;
// }

// void display_pulse_duration() {
//   if (last_displayed != pulse_duration) {
//     lcd.setCursor(0, 1);
//     lcd.printf("%dus     ", pulse_duration);
//     last_displayed = pulse_duration;
//   }
// }
