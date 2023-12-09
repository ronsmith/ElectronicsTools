
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
  delay(1000);
}

