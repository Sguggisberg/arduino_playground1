volatile int index_of_data;
int frequency_in_hz;

const int data_pin[] = { 2, 3, 4, 5, 6, 7 };
const float signal[] = { 2, 3, 4.5, 3, 2 };
const int num_data_pins = 6;
const int v_supply = 5;  // Powersupply in [V]

void setup() {
  Serial.begin(9600);
  index_of_data = 0;
  frequency_in_hz = 1;
  setupDacOutput();
  setupTimer();
}

void setupTimer() {
  // initialize Timer1
  noInterrupts();
  TCCR1A = 0;  // set entire TCCR1A register to 0
  TCCR1B = 0;  // same for TCCR1B
  TCNT1 = 0;
  OCR1A = (16 * pow(10, 6)) / (frequency_in_hz * 1024) - 1;  // (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();  // enable all interrupts
}

void setupDacOutput() {
  for (int i = 0; i < num_data_pins; i++) {
    pinMode(data_pin[i], OUTPUT);
  }
}

void loop() {
  Serial.println("I am the main program - and I am bored!");
  delay(5000);
}

void sendToDac(int value_in_dec) {
  for (int i = 0; i < num_data_pins; i++) {
    if ((value_in_dec & (1 << (num_data_pins - 1 - i))) != 0) {
      digitalWrite(data_pin[i], HIGH);
    } else {
      digitalWrite(data_pin[i], LOW);
    }
  }
}

// Umrechnung Spannung zu Dezimal für die Leds
int calcVoltageInDec(float voltage) {
  float lsb = v_supply / pow(2, num_data_pins);
  return (voltage / lsb);
}

ISR(TIMER1_COMPA_vect) {
  sendToDac(calcVoltageInDec(signal[index_of_data]));
  index_of_data = (index_of_data + 1) % 5;
}
