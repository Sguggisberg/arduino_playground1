#include <Arduino.h>

uint8_t pause = 200;
uint8_t clkPin = 13;
uint8_t clearPin = 12;
uint8_t dataPin = 11;
uint8_t enablePin = 10;

byte data = 0xA;

void disableShiftOutput();
void clearShiftRegister();
void sendData() ;
void setDataToShiftRegister();
void enableShiftOutput();

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
  setDataToShiftRegister();
  enableShiftOutput();
}


void setDataToShiftRegister() {
  shiftOut(dataPin, clkPin, LSBFIRST, data);
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
