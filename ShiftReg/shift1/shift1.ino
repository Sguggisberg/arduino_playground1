uint8_t pause = 200;
uint8_t clkPin = 13;
uint8_t clearPin = 12;
uint8_t dataPin = 11;
uint8_t enablePin = 10;

boolean data[] = { 1, 1, 0, 0, 1, 1, 1, 0 };

bool done = false;
void setup() {
  Serial.begin(9600);
  pinMode(clkPin, OUTPUT);
  pinMode(clearPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  disableShiftOutput();
  clearShiftRegister();
}

void loop() {
  if (!done) {
    sendData();
    done = true;
  }

  delay(pause);
}

void sendData() {
  disableShiftOutput();
  for (int i = sizeof(data); i >= 0; i--) {
    clkLow();
    setDataToShiftRegister(data[i]);
    clkHigh();
    delay(pause);
  }
  enableShiftOutput();
}


void setDataToShiftRegister(bool level) {
  digitalWrite(dataPin, level);
}

void clkHigh() {
  digitalWrite(clkPin, HIGH);
}

void clkLow() {
  digitalWrite(clkPin, LOW);
}

void enableShiftOutput() {
  digitalWrite(enablePin, HIGH);
}

void disableShiftOutput() {
  digitalWrite(enablePin, LOW);
}

void clearShiftRegister() {
  digitalWrite(clearPin, LOW);
  delay(pause);
  digitalWrite(clearPin, HIGH);
}
