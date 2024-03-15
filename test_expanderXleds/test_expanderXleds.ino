#include <Adafruit_PCF8575.h>
#include <Wire.h>

const uint8_t PinSda = 4;
const uint8_t PinScl = 5;

// Pins am Expander
// out = LED-Kathode
const uint8_t EPinLed1out = 7;
const uint8_t EPinLed2in = 6;
const uint8_t EPinLed3in = 4;
const uint8_t EPinLed3out = 5;

const uint8_t I2cExpanderPort = 0x20;

Adafruit_PCF8575 expander;


void fehlerblinken() {
  static const uint8_t OnBoardLed = 2;
  pinMode(OnBoardLed, OUTPUT);
  while (1) {
    digitalWrite(OnBoardLed, HIGH);
    delay(200);
    digitalWrite(OnBoardLed, LOW);
    delay(200);
  }
}

void setup() {
  if (!Wire.setPins(PinSda, PinScl))
    fehlerblinken();
  if (!expander.begin(I2cExpanderPort))
    fehlerblinken();
}

void loop() {
  // LED-Anschlüsse:
  // 0 an VDD und GND
  // 1 an VDD und Pin
  // 2 an Pin und GND
  // 3 an Pin und Pin

  // Test 1: keine Anpassungen
  /**/
  delay(200);
  /**/
  // -> leuchtende LEDs: 0, 2 (aber: je nach letztem Zustand)

  // Test 2: erleuchte LED 1
  /**/
  expander.pinMode(EPinLed1out, OUTPUT);
  expander.digitalWrite(EPinLed1out, LOW);
  // -> Obacht: Ziehen auf LOW führt zum Leuchten!
  /**/

  // Test 3: erhelle LED 2
  /**/
  expander.pinMode(EPinLed2in, INPUT);
  /**/

  // Test 4: Erleuchte LED 3
  /**/
  expander.pinMode(EPinLed3in, INPUT);
  expander.pinMode(EPinLed3out, OUTPUT);
  expander.digitalWrite(EPinLed3out, LOW);
  /**/
}
