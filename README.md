# Lebenszeitablauf

## Ziel

Gewünscht ist ein Sekundenzähler, der allerdings ab einer vorgegebenen Zahl
(z.B. 30 Jahre) abwärts zählt.

Angezeigt werden sollen die verbleibenden Sekunden mittels LED-Ziffern
(7-Segment-Anzeige).

--------------------------------------------------------------------------------

# Entwicklungstagebuch

## 7-Segment-Anzeige

Für 30 Jahre werden bereits neun Ziffern benötigt;
die gängigen fertigen Lösungen bieten höchstens acht
(die dann allerdings bereits mit einem eigenen Controller einfach angesteuert werden können).

Gefunden habe ich letztlich eine Lösung mit fünf Ziffern,
sodass zwei davon für die geforderte Aufgabe ausreichen sollten.

### Ansteuerung eines 5-Ziffern-Bauteils

Jeder dieser 5-Ziffern-Bausteine hat allerdings bereits 13 Verbindungspunkte,
die alle benötigt werden;
somit ergeben sich bei zwei dieser Bausteine 26 benötigte Pins.
(Ein üblicher ESP32 hat 25 GPIO-Pins, also genau einen zu wenig.)

Lösungsmöglichkeiten:
- Pins sparen: Da die Punkte der 7-Segment-Anzeige (also das jeweils achte Segment)
  nicht benötigt werden, genügen pro Baustein 12 Verbindungen.
  Da die Aufgabe mit einem Arduino Nano mit 20 GPIO-Pins gelöst werden soll, sind dies allerdings immer noch zu viele.
  (Es wäre aber ein interessanter Zwischenschritt auf dem Weg zur endgültigen Lösung.)
- IO-Expander: Die Anzahl der nutzbaren Pins kann via Baustein erhöht werden.
- Eigenen Mikrocontroller pro 5-Ziffern-Anzeige programmieren und die beiden dann ansteuern.
  (Dies könnte die interessanteste Vorgehensweise sein - allerdings auch die hardware-aufwendigste.)

### Anzeigen fünf verschiedener Ziffern pro Bauteil

Die vorgegebene Verdrahtung lässt bei konstantem Strom auf allen fünf Ziffern
nur die gleiche Anzeige erscheinen
(oder gar keine, wenn der Ausgang der Ziffer nicht geschaltet ist).

Die Ansteuerung muss also im millisekunden-gesteuerten Wechsel erfolgen.

Auch abhängig von der gewählten Lösung des Anschlusses der beiden Bausteine ist
die Taktung des Wechsels zwischen den Ziffern:
Kann jede Ziffer bei einem Fünftel oder einem Zehntel der Zeit angesteuert werden?

## Test 1: Fünfstellige Zahlen anzeigen

Ein erstes kleines Testprogramm soll die Darstellung
beliebiger fünfstelliger Zahlen in einem Anzeigebauteil ermöglichen.

Im ersten Versuch will die Arduino IDE mich weder Funktionen mit std::bitset als Parameter
definieren lassen noch mir einen vernünftigen seriellen Output anzeigen.
Zudem wird die fünfte Ziffer nicht mit angezeigt.

Zum zweiten Punkt habe ich den Verdacht, dass eventuell einer der benutzten Pins
mit zum Serial gehört;
zum dritten, dass eventuell eine Verkabelung nicht stimmt.

Für einen Abend war das aber erst einmal genug angesammelter Frust
und es geht wann anders weiter.

Hinweis: Grundsätzlich sollte die Bitset-Parameterübergabe funktionieren,
die einschlägigen Online-Compiler unterstützen dies alles.
Ist es vielleicht zu viel C++ für den Arduino-C-Compiler?

ToDo: Die Initialisierungsstrings der Bitsets müssen noch umgedreht werden,
sie sind von hinten nach vorne zu lesen.


