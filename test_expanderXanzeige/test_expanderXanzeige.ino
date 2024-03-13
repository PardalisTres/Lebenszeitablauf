#include <PCF8575.h>  // https://github.com/RobTillaart/PCF8575
#include <Wire.h>
#include <bitset>

const uint8_t PinSda = 2;
const uint8_t PinScl = 4;

const uint8_t I2cPortExpander = 0x20;

PCF8575 expander(I2cPortExpander);

// Pins am Expander für Pins der Display-Blöcke
// (x = Ausfluss-Pin, - = nicht vorhanden)
//   Block 1 (Pin1 - Pin14, ohne Pin 7):
//     4,  3, 2,  1,  0,  x, -,
//     x, 12, x,  x, 11, 10, x
//   Block 2:
//     7,  6, 5, 16, 17,  x, -,
//     x, 15, x,  x, 14, 13, x

// Pins am Controller für Ausfluss-Pins der
// jeweils beiden n-ten Stellen der Anzeige:
//   DPin CPin
//     6   33
//     8   25
//    10   32
//    11   22
//    14   23

// Pins am Expander für die Ansteuerung (Ausgabe) der acht Segmente an den beiden Blöcken
// (0 = Segment A, ..., 8 = Punkt-Segment)
const uint8_t EPinForSegmentOnBlock1[] = {
  // 13, 9, 4, 2, 1, 12, 5, 3 (am Block)
  10, 12, 1, 3, 4, 11, 0, 2
};
const uint8_t EPinForSegmentOnBlock2[] = {
  // 13, 9, 4, 2, 1, 12, 5, 3 (am Block)
  13, 15, 16, 6, 7, 14, 17, 5
};

// Pins am Controller für die Ansteuerung (Ausfluss) der fünf Ziffern an beiden Blöcken
// (0 = hinterste Stelle pro Block)
const uint8_t PinForDigit[] = {
  // 8, 6, 10, 11, 14 (am Block)
  25, 33, 32, 22, 23
};

// Bit-Muster für Ziffern
const std::bitset<8> Muster0{ "00111111" };
const std::bitset<8> Muster1{ "00000110" };
const std::bitset<8> Muster2{ "01011011" };
const std::bitset<8> Muster3{ "01001111" };
const std::bitset<8> Muster4{ "01100110" };
const std::bitset<8> Muster5{ "01101101" };
const std::bitset<8> Muster6{ "01111101" };
const std::bitset<8> Muster7{ "00000111" };
const std::bitset<8> Muster8{ "01111111" };
const std::bitset<8> Muster9{ "01101111" };
//
const std::bitset<8> MusterZiffer[10] = {
  Muster0, Muster1, Muster2, Muster3, Muster4,
  Muster5, Muster6, Muster7, Muster8, Muster9
};



void displaySetZifferAn(const uint8_t stelle, bool an = true) {
  pinMode(PinForDigit[stelle], an ? OUTPUT : INPUT);
}

void displayShowZiffer(const uint8_t ziffer) {
  const std::bitset<8>& muster = MusterZiffer[ziffer];
  for (uint8_t i = 0; i < 8; ++i) {
    expander.write(EPinForSegmentOnBlock1[i], muster[i] ? HIGH : LOW);
    expander.write(EPinForSegmentOnBlock2[i], muster[i] ? HIGH : LOW);
  }
}



void setup() {
  expander.begin(PCF8575_INITIAL_VALUE);

  // zunächst alle Anzeigestellen ausschalten
  for (auto pin : PinForDigit) {
    pinMode(pin, INPUT);
  }
}

void loop() {
  // Für den Beginn lassen wir erst einmal die Stellen durchlaufen
  // und geben jeweils die Stellennummer aus:
  /**/
  for (uint8_t i = 0; i < 5; ++i) {
    displaySetZifferAn((i + 4) % 5, false); // i-1 funktioniert nicht
    displayShowZiffer(i + 1);
    displaySetZifferAn(i, true);
    delay(500);
  }
  /**/
}
