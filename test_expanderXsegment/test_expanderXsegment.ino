#include <PCF8575.h> // https://github.com/RobTillaart/PCF8575
#include <Wire.h>

const uint8_t PinSda = 2;
const uint8_t PinScl = 4;

const uint8_t I2cPortExpander = 0x20;

PCF8575 expander(I2cPortExpander);

// d2e[0] ist der Pin des Expanders, der zu Pin0 der 5x7-Segmentanzeige gehört
// (Pin0, Pin7 gibt es nicht an der Anzeige)
const uint8_t displayToExpander[] = {0, 1, 2, 3, 4, 5, 6, 0, 16, 15, 14, 13, 12, 11, 10};


void setupExpander(){
  expander.begin(PCF8575_INITIAL_VALUE);
  // const uint16_t mask = ...
  expander.setButtonMask(0xFFFF);
}

void loopExpander() {
  expander.write16(0);
  expander.write(displayToExpander[5], HIGH); // Input für Mittelstreifen
  expander.write(displayToExpander[13], LOW); // Output für erste Ziffer
  // expander.read(displayToExpander[14]);
  delay(100);
}










void setup() {
  // setupI2c();
  setupExpander();
}

void loop() {
  // loopI2c();
  loopExpander();
}
