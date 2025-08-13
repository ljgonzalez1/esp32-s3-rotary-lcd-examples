#include <Arduino.h>
#include "libs_import.h"

#ifndef USB_MONITOR_BAUD
#define USB_MONITOR_BAUD 115200
#endif

static void banner(const char* msg) {
  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(msg);
  Serial.println(F("=================================================="));
}

void setup() {
  /* USB CDC */
  Serial.begin(USB_MONITOR_BAUD);
  while (!Serial) { delay(10); }
  banner("ESP32-S3 Knob — Include check");

  /* Reporte IO Expander */
#if V_HAVE_IOEXP
  Serial.print(F("IO_Expander header: ")); Serial.println(F(V_IOEXP_HDR));
#else
  Serial.println(F("IO_Expander header: NOT FOUND"));
#endif

#if V_HAVE_UTILS
  Serial.print(F("esp-lib-utils header: ")); Serial.println(F(V_UTILS_HDR));
#else
  Serial.println(F("esp-lib-utils header: NOT FOUND (ok si no lo usas directo)"));
#endif

#if V_HAVE_IOEXP && IOEXP_ENABLE
  banner("IO_Expander smoke test");
  using namespace ioexpander_factory;
  auto* exp = create();
  /* Pin 0 como salida y toggle */
  exp->pinMode(0, OUTPUT);
  exp->digitalWrite(0, HIGH);
  delay(50);
  exp->digitalWrite(0, LOW);
  delay(50);
  Serial.println(F("Expander init OK, pin0 toggled."));
  delete exp;
#else
  Serial.println(F("IOEXP_ENABLE=0 (no se inicializa el expansor; solo se probó el include)."));
#endif

  Serial.println();
  Serial.println(F("Done."));
}

void loop() {
  delay(500);
}
