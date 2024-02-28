#include <bitset>

// ESP-GPIO-Pins, die zu den Pins der Anzeige führen.
// (Pin 0 und 7 gibt es nicht; 3 ist für den . und somit nicht benötigt.)
const uint8_t DisplayPins[15] = { 0, 19, 21, 3, 1, 22, 23, 0, 34, 35, 32, 33, 25, 26, 27 };

// Bit-Muster für Ziffern
const std::bitset<8> Muster0{ "11111100" };
const std::bitset<8> Muster1{ "01100000" };
const std::bitset<8> Muster2{ "11011010" };
const std::bitset<8> Muster3{ "11110010" };
const std::bitset<8> Muster4{ "01100110" };
const std::bitset<8> Muster5{ "10110110" };
const std::bitset<8> Muster6{ "10111110" };
const std::bitset<8> Muster7{ "11100000" };
const std::bitset<8> Muster8{ "11111110" };
const std::bitset<8> Muster9{ "11110110" };

// Zu Stelle i gehört folgender DisplayPin als Ausgang (Ground)
const uint8_t PinZuStelleGnd[] = { 14, 11, 10, 6, 8 };

// Zu Segment i gehört folgender DisplayPin als Eingang (Vcc)
const uint8_t PinZuStelleVcc[] = { 13, 9, 4, 2, 1, 12, 5, 3 };


void displaySetZifferAn(const uint8_t stelle, bool an = true) {
  // TODO: ist OUTPUT der richtige Parameter, wenn der Pin weggeschaltet werden soll? oder INPUT_PULLUP?
  pinMode(DisplayPins[PinZuStelleGnd[stelle]], an ? OUTPUT : INPUT);
  Serial.print("displaySetZifferAn(");
  Serial.print(stelle);
  Serial.print(", ");
  Serial.print(an);
  Serial.println(")");
}

void displayShowZiffer(/*const std::bitset<8>& muster*/) {
  for (uint8_t i = 0; i < 8; ++i) {
    // digitalWrite(DisplayPins[PinZuStelleVcc[i]], muster[i] ? HIGH : LOW);
    digitalWrite(DisplayPins[PinZuStelleVcc[i]], i % 2 == 0 ? HIGH : LOW);
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

  displayShowZiffer();
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

  // neue Lichter an
  displaySetZifferAn(stelle, true);
}