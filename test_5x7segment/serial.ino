void setupSerial() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }

  // Bei nur einer Sekunde Wartezeit wird der Programmname noch nicht ausgegeben,
  // deswegen spendieren wir hier direkt zwei Minuten.
  delay(2000);

  Serial.println();
  Serial.println(PROGRAM_NAME);
  Serial.print(__DATE__);
  Serial.print(" - ");
  Serial.println(__TIME__);
  Serial.println();
}
