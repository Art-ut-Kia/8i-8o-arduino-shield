/******************************************************************************
 * Test8i8o_binary.ino :       8 input / 8 output OUDEIS shield test          *
 *    Outputs : Set LEDs status on reception of 1 byte (1 bit per LED)        *
 *    Inputs : On reception of a LED status command byte, replies by sending  *
 *             another byte containing switches status (1 bit per switch)     *
 ******************************************************************************/

// LED control pins definition
const unsigned char LC[8] = {10,  9,  8, 11,  7,  6,  5,  4};
// switches reading pins definition
const unsigned char SW[8] = {A0, A1, A2, A3, A4, A5,  2,  3};

void setup() {
  // open serial port
  Serial.begin(9600);
  // set LEDs control pins as output
  for (int i = 0; i < 8; i++) pinMode(LC[i], OUTPUT);
  // set switches reading pins as input
  for (int i = 0; i < 8; i++) pinMode(SW[i], INPUT);
}

void loop() {
  if (Serial.available() > 0) { // if a character is received
    // reads it
    unsigned char c = Serial.read();
    // parses its bits one after the other ...
    for (int i = 0; i < 8; i++) {
      // ... to control the 8 LED's accordingly
      digitalWrite( LC[i], (c & 1) ? HIGH : LOW );
      c >>= 1;
    }

    // reads the 8 switches and transmits their statuses over the 8 bits of a character
    c = 0;
    for (int i = 0; i < 8; i++) {
      c >>= 1;
      if (digitalRead(SW[i]) == HIGH) c |= 128;
    }
    Serial.write(c);
  }
}
