#include <Arduino.h>

#ifndef USB_MONITOR_BAUD
#define USB_MONITOR_BAUD 115200
#endif

#ifndef PRINT_MESSAGE
#define PRINT_MESSAGE "[ESP32-S3] Hello from Serial!"
#endif

static void banner(const char* msg) {
  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(msg);
  Serial.println(F("=================================================="));
}

void setup() {
  Serial.begin(USB_MONITOR_BAUD);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(50); }

  banner("==== Setup start ====");

  Serial.println(PRINT_MESSAGE);

  banner("==== Setup end ====");
}

void loop() {
  delay(1000); // idle
}
