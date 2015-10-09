/******************************************************************************
 * Test8i8o.ino :          8 input / 8 output OUDEIS shield test              *
 * 1) outputs :                                                               *
 *    - switches on LEDs 1..8 on reception of 'A'..'H'                        *
 *    - switches off LEDs 1..8 on reception of 'a'..'h'                       *
 * 2) inputs : sends "01100111" string on reception of '?'                    *
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
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c>='A' && c<='H') digitalWrite(LC[c-'A'], HIGH);
    if (c>='a' && c<='h') digitalWrite(LC[c-'a'], LOW);
    if (c=='?') {
      for (int i = 0; i < 8; i++)
        Serial.write(digitalRead(SW[i]) == HIGH ? '1' : '0');
      Serial.println();
    }
  }
}
