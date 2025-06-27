volatile int counter = 0;
int frequency_in_hz = 2;

void setup() {
  // initialize Timer1
  noInterrupts();  
  TCCR1A = 0;      // set entire TCCR1A register to 0
  TCCR1B = 0;      // same for TCCR1B
  TCNT1 = 0;       
  OCR1A = (16 * pow(10, 6)) / (frequency_in_hz * 1024) - 1; // (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();  // enable all interrupts
  Serial.begin(9600);
}

void loop() {
  Serial.print("Main Program: ");
  Serial.println(counter);
  Serial.println(OCR1A);

  delay(5000);
}

ISR(TIMER1_COMPA_vect) {

  counter++;  //Counter increases by 1 every second
  Serial.print("Timer: ");
  Serial.println(counter);
}
