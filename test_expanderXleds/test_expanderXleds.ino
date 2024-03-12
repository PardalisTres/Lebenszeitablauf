#include <PCF8575.h>  // https://github.com/RobTillaart/PCF8575
#include <Wire.h>

const uint8_t PinSda = 2;
const uint8_t PinScl = 4;

// Pins am Expander
// out = LED-Kathode
const uint8_t EPinLed1out = 16;
const uint8_t EPinLed2in = 14;
const uint8_t EPinLed3in = 4;
const uint8_t EPinLed3out = 5;

const uint8_t I2cPortExpander = 0x20;

PCF8575 expander(I2cPortExpander);


void setup() {
  expander.begin(PCF8575_INITIAL_VALUE);

  // expander.setButtonMask(0xFFFF);
  // expander.setButtonMask(0x0000);
  // -> Ich kann keinen Unterschied im Verhalten beim Setzen dieser Maskierungen sehen.
}

void loop() {
  // LED-Anschlüsse:
  // 0 an VDD und GND
  // 1 an VDD und Pin
  // 2 an Pin und GND
  // 3 an Pin und Pin

  // Test 1: keine Anpassungen
  // -> leuchtende LEDs: 0, 2

  // Test 2: erleuchte LED 1
  /**/
  // expander.write(EPinLed1out, LOW);
  // expander.write(EPinLed1out, HIGH);
  // expander.readButton(EPinLed1out);
  /**/
  // -> kein positives Ergebnis mit allen Methoden

  // Test 3: verdunkle LED 2
  /**/
  // expander.write(EPinLed2in, HIGH);
  // expander.write(EPinLed2in, LOW);
  // expander.selectNone();
  // expander.selectAll();
  /**/
  // -> kein positives Ergebnis mit allen Methoden

  // Test 4: Erleuchte LED 3
  /**/
  // expander.write(EPinLed3in, HIGH);
  // expander.write(EPinLed3out, LOW);
  //
  // expander.write(EPinLed3in, LOW);
  // expander.write(EPinLed3out, HIGH);
  /**/
  // -> kein positives Ergebnis mit allen Methoden
}
