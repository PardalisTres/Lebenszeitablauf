void setupSerial() {
  // Ganze fünf Sekunden Delay jeweils, um genug Zeit für langsame Entwicklungsrechner oder zum Start weiterer Programme zu haben (z.B. puTTy).
  // delay(5000);
  Serial.begin(9600);
  while (!Serial) {
    delay(100);
  }
  // delay(5000);

  Serial.println();
  Serial.print(PROGRAM_NAME);
  Serial.println();
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.print(__TIME__);
  Serial.println();
}
