#include <Arduino.h>

#ifndef USB_MONITOR_BAUD
#define USB_MONITOR_BAUD 115200
#endif

// ---------------------------------------------------------------------
// Include each vendor module conditionally (so build never breaks
// if a header renames). We only "touch" headers + print that they
// were seen by the compiler/linker.
// ---------------------------------------------------------------------

// ---- LVGL ----
#if __has_include(<lvgl.h>)
#include <lvgl.h>
  #define HAVE_LVGL 1
#else
#define HAVE_LVGL 0
#endif

// ---- ESP32_Display_Panel ----
#if __has_include(<ESP_Panel_Library.h>)
#include <ESP_Panel_Library.h>
  #define HAVE_PANEL 1
#elif __has_include(<esp_panel.hpp>)
#include <esp_panel.hpp>
  #define HAVE_PANEL 1
#elif __has_include(<ESP32_Display_Panel.h>)
#include <ESP32_Display_Panel.h>
  #define HAVE_PANEL 1
#else
#define HAVE_PANEL 0
#endif

// ---- ESP32_IO_Expander ----
#if __has_include(<ESP_IOExpander.hpp>)
#include <ESP_IOExpander.hpp>
  #define HAVE_IOEXP 1
#elif __has_include(<ESP_IOExpander.h>)
#include <ESP_IOExpander.h>
  #define HAVE_IOEXP 1
#else
#define HAVE_IOEXP 0
#endif

// ---- ESP32_Button ----
#if __has_include(<ESP32_Button.h>)
#include <ESP32_Button.h>
  #define HAVE_BUTTON 1
#elif __has_include(<Button.h>)
#include <Button.h>
  #define HAVE_BUTTON 1
#else
#define HAVE_BUTTON 0
#endif

// ---- ESP32_Knob ----
#if __has_include(<ESP32_Knob.h>)
#include <ESP32_Knob.h>
  #define HAVE_KNOB 1
#else
#define HAVE_KNOB 0
#endif

// ---- esp-lib-utils ----
#if __has_include(<esp_utils.h>)
#include <esp_utils.h>
  #define HAVE_UTILS 1
#elif __has_include(<ESP_Utils.h>)
#include <ESP_Utils.h>
  #define HAVE_UTILS 1
#else
#define HAVE_UTILS 0
#endif

// ---- ui (SquareLine export) ----
#if __has_include(<ui.h>)
#include <ui.h>
  #define HAVE_UI 1
#else
#define HAVE_UI 0
#endif

// Pretty printer helpers
static void banner(const char* msg) {
  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(msg);
  Serial.println(F("=================================================="));
}

static void print_lib_state(const char* name, bool ok, const char* extra = nullptr) {
  if (ok) {
    Serial.print(F("[OK] ")); Serial.print(name);
    if (extra) { Serial.print(F(" ")); Serial.print(extra); }
    Serial.println();
  } else {
    Serial.print(F("[--] ")); Serial.print(name); Serial.println(F(" (header not found)"));
  }
}

void setup() {
  Serial.begin(USB_MONITOR_BAUD);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(20); }

  banner("VIEWE libs import check");

#if HAVE_LVGL
  // Show LVGL version if available (does not initialize LVGL runtime)
  char ver[32];
  snprintf(ver, sizeof(ver), "v%d.%d.%d", LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);
  print_lib_state("LVGL", true, ver);
#else
  print_lib_state("LVGL", false);
#endif

  print_lib_state("ESP32_Display_Panel", HAVE_PANEL);
  print_lib_state("ESP32_IO_Expander",  HAVE_IOEXP);
  print_lib_state("ESP32_Button",       HAVE_BUTTON);
  print_lib_state("ESP32_Knob",         HAVE_KNOB);
  print_lib_state("esp-lib-utils",      HAVE_UTILS);
  print_lib_state("ui (SquareLine)",    HAVE_UI);

  Serial.println();
  Serial.println(F("All modules included (where headers were found)."));
}

void loop() {
  // Idle so we don't saturate USB/CPU
  delay(1000);
}
