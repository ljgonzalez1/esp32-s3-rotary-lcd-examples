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
static void report(const char* name, const char* hdr, bool ok) {
  if (ok) {
    Serial.print(F("[OK] ")); Serial.print(name);
    Serial.print(F("  <")); Serial.print(hdr); Serial.println(F(">"));
  } else {
    Serial.print(F("[--] ")); Serial.print(name);
    Serial.println(F("  (header not found)"));
  }
}

void setup() {
  Serial.begin(USB_MONITOR_BAUD);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(25); }

  banner("VIEWE libs import check");

#if V_HAVE_LVGL
  report("LVGL", V_LVGL_HDR, true);
#else
  report("LVGL", "", false);
#endif

#if V_HAVE_PANEL
  report("ESP32_Display_Panel", V_PANEL_HDR, true);
#else
  report("ESP32_Display_Panel", "", false);
#endif

#if V_HAVE_IOX
  report("ESP32_IO_Expander", V_IOX_HDR, true);
#else
  report("ESP32_IO_Expander", "", false);
#endif

#ifdef V_HAVE_BTN
  report("ESP32_Button", V_BTN_HDR, true);
#else
  report("ESP32_Button", "", false);
#endif

#ifdef V_HAVE_KNOB
  report("ESP32_Knob", V_KNOB_HDR, true);
#else
  report("ESP32_Knob", "", false);
#endif

#ifdef V_HAVE_UTILS
  report("esp-lib-utils", V_UTILS_HDR, true);
#else
  report("esp-lib-utils", "", false);
#endif

#ifdef V_HAVE_UI
  report("ui (SquareLine)", V_UI_HDR, true);
#else
  report("ui (SquareLine)", "", false);
#endif

  viewe_touch_symbols_minimal();

  Serial.println();
  Serial.println(F("All modules included (where headers were found)."));
}

void loop() {
  delay(500);
}
