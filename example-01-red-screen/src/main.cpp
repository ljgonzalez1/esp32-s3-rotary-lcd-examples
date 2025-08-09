#include <Arduino.h>

// Minimal example: print "Hello, world" to Serial every 5 seconds.
// Notes:
//  - Uses a short, non-blocking wait for USB CDC so it doesn't hang if no host is attached.
//  - Baud rate must match your serial monitor (115200 by default).

void setup() {
  Serial.begin(115200);

  // Wait up to 2 seconds for a host to open the USB CDC port (optional)
  const uint32_t t0 = millis();
  while (!Serial && (millis() - t0) < 2000) {
    delay(10);
  }

  Serial.println("Hello, world");
}

void loop() {
  // Repeat every 5 seconds
  delay(5000);
  Serial.println("Hello, world");
}
