// #include <bitset>

// ESP-GPIO-Pins, die zu den Pins der Anzeige führen.
// (Pin 0 und 7 gibt es nicht; 3 ist für den . und somit nicht benötigt.)
const uint8_t DisplayPins[15] = { 0, 19, 21, 3, 1, 22, 23, 0, 34, 35, 32, 33, 25, 26, 27 };

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
const std::bitset<8> MusterZiffer[10] = { Muster0, Muster1, Muster2, Muster3, Muster4, Muster5, Muster6, Muster7, Muster8, Muster9 };

// Zu Stelle i gehört folgender DisplayPin als Ausgang (Ground)
const uint8_t PinZuStelleGnd[] = { 14, 11, 10, 6, 8 };

// Zu Segment i gehört folgender DisplayPin als Eingang (Vcc)
const uint8_t PinZuStelleVcc[] = { 13, 9, 4, 2, 1, 12, 5, 3 };


void displaySetZifferAn(const uint8_t stelle, bool an = true) {
  // TODO: ist OUTPUT der richtige Parameter, wenn der Pin weggeschaltet werden soll? oder INPUT_PULLUP?
  // -> OUTPUT schein es zu tun.

  pinMode(DisplayPins[PinZuStelleGnd[stelle]], an ? OUTPUT : INPUT);
  Serial.print("displaySetZifferAn(");
  Serial.print(stelle);
  Serial.print(", ");
  Serial.print(an);
  Serial.println(")");
}

void displayShowZiffer(const std::bitset<8>& muster) {
  for (uint8_t i = 0; i < 8; ++i) {
    digitalWrite(DisplayPins[PinZuStelleVcc[i]], muster[i] ? HIGH : LOW);
  }
}




void setupDisplay() {
  pinMode(DisplayPins[13], OUTPUT);
  pinMode(DisplayPins[9], OUTPUT);
  pinMode(DisplayPins[4], OUTPUT);
  pinMode(DisplayPins[2], OUTPUT);
  pinMode(DisplayPins[1], OUTPUT);
  pinMode(DisplayPins[12], OUTPUT);
  pinMode(DisplayPins[5], OUTPUT);

  // pinMode(DisplayPins[14], INPUT);
  // pinMode(DisplayPins[11], INPUT);
  // pinMode(DisplayPins[10], INPUT);
  // pinMode(DisplayPins[6], INPUT);
  // pinMode(DisplayPins[8], INPUT);
}

void loopDisplay() {
  static const uint32_t zyklus{ 5000 };
  static uint32_t lastTime{ -zyklus };
  static uint8_t stelle{ 0 };

  if (millis() - lastTime < zyklus) return;

  lastTime = millis();
  Serial.println("[loopDisplay]");

  // alte Lichter aus
  displaySetZifferAn(stelle, false);

  // Anzeigestelle wechseln
  stelle = ++stelle % 5;

  // angezeigte Ziffer wechseln
  displayShowZiffer(MusterZiffer[stelle]);

  // neue Lichter an
  displaySetZifferAn(stelle, true);
}
