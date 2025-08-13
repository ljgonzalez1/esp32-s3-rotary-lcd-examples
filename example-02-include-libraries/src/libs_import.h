#pragma once
#include <Arduino.h>

/* Helpers para imprimir qué header se tomó */
#ifndef V_STR
#define V_XSTR(x) #x
#define V_STR(x)  V_XSTR(x)
#endif

/* ========= LVGL ========= */
#if __has_include(<lvgl.h>)
#include <lvgl.h>
  #define V_HAVE_LVGL 1
  #define V_LVGL_HDR  "lvgl.h"
#elif __has_include(<lvgl/lvgl.h>)
#include <lvgl/lvgl.h>
  #define V_HAVE_LVGL 1
  #define V_LVGL_HDR  "lvgl/lvgl.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/lvgl-release-v8.4/lvgl.h")
#include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/lvgl-release-v8.4/lvgl.h"
  #define V_HAVE_LVGL 1
  #define V_LVGL_HDR  "third_party/.../lvgl-release-v8.4/lvgl.h"
#endif

/* ===== ESP32_Display_Panel ===== */
#if __has_include(<ESP_Panel_Library.h>)
#include <ESP_Panel_Library.h>
  #define V_HAVE_PANEL 1
  #define V_PANEL_HDR "ESP_Panel_Library.h"
#elif __has_include(<ESP_Panel.h>)
#include <ESP_Panel.h>
  #define V_HAVE_PANEL 1
  #define V_PANEL_HDR "ESP_Panel.h"
#elif __has_include(<ESP32_Display_Panel.h>)
#include <ESP32_Display_Panel.h>
  #define V_HAVE_PANEL 1
  #define V_PANEL_HDR "ESP32_Display_Panel.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Display_Panel/src/ESP_Panel_Library.h")
#include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Display_Panel/src/ESP_Panel_Library.h"
  #define V_HAVE_PANEL 1
  #define V_PANEL_HDR "third_party/.../ESP32_Display_Panel/src/ESP_Panel_Library.h"
#endif

/* ===== ESP32_IO_Expander ===== */
#if __has_include(<ESP_IOExpander.hpp>)
#include <ESP_IOExpander.hpp>
  #define V_HAVE_IOX 1
  #define V_IOX_HDR "ESP_IOExpander.hpp"
#elif __has_include(<ESP_IOExpander.h>)
#include <ESP_IOExpander.h>
  #define V_HAVE_IOX 1
  #define V_IOX_HDR "ESP_IOExpander.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_IO_Expander/src/ESP_IOExpander.hpp")
#include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_IO_Expander/src/ESP_IOExpander.hpp"
  #define V_HAVE_IOX 1
  #define V_IOX_HDR "third_party/.../ESP32_IO_Expander/src/ESP_IOExpander.hpp"
#endif

/* ===== ESP32_Button ===== */
#if __has_include(<Button.h>)
#include <Button.h>
  #define V_HAVE_BTN 1
  #define V_BTN_HDR "Button.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Button/src/Button.h")
#include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Button/src/Button.h"
  #define V_HAVE_BTN 1
  #define V_BTN_HDR "third_party/.../ESP32_Button/src/Button.h"
#endif

/* ===== ESP32_Knob ===== */
#if __has_include(<ESP_Knob.h>)
#include <ESP_Knob.h>
  #define V_HAVE_KNOB 1
  #define V_KNOB_HDR "ESP_Knob.h"
#elif __has_include(<Knob.h>)
#include <Knob.h>
  #define V_HAVE_KNOB 1
  #define V_KNOB_HDR "Knob.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Knob/src/ESP_Knob.h")
#include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Knob/src/ESP_Knob.h"
  #define V_HAVE_KNOB 1
  #define V_KNOB_HDR "third_party/.../ESP32_Knob/src/ESP_Knob.h"
#endif

/* ===== esp-lib-utils ===== */
#if __has_include(<esp_utils.h>)
#include <esp_utils.h>
  #define V_HAVE_UTILS 1
  #define V_UTILS_HDR "esp_utils.h"
#elif __has_include(<esp_utils_conf.h>)
#include <esp_utils_conf.h>
  #define V_HAVE_UTILS 1
  #define V_UTILS_HDR "esp_utils_conf.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/esp-lib-utils/src/esp_utils.h")
#include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/esp-lib-utils/src/esp_utils.h"
  #define V_HAVE_UTILS 1
  #define V_UTILS_HDR "third_party/.../esp-lib-utils/src/esp_utils.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/esp-lib-utils/esp_utils_conf.h")
// a veces este está en la raíz
  #include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/esp-lib-utils/esp_utils_conf.h"
  #define V_HAVE_UTILS 1
  #define V_UTILS_HDR "third_party/.../esp-lib-utils/esp_utils_conf.h"
#endif

/* ===== ui (SquareLine) ===== */
#if __has_include(<ui.h>)
#include <ui.h>
  #define V_HAVE_UI 1
  #define V_UI_HDR "ui.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ui/ui.h")
#include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ui/ui.h"
  #define V_HAVE_UI 1
  #define V_UI_HDR "third_party/.../ui/ui.h"
#endif

/* “Tocar” símbolos mínimos para que el linker coja las unidades */
inline void viewe_touch_symbols_minimal() {
#ifdef V_HAVE_LVGL
  lv_init(); // safe sin drivers
#endif
#ifdef V_HAVE_BTN
  (void)sizeof(Button);
#endif
#ifdef V_HAVE_KNOB
  (void)sizeof(ESP_Knob);
#endif
#ifdef V_HAVE_IOX
  (void)sizeof(ESP_IOExpander);
#endif
#ifdef V_HAVE_PANEL
  // la mayoría exponen ESP_Panel; si no, no pasa nada
  #ifdef ESP_Panel
    (void)sizeof(ESP_Panel);
  #endif
#endif
#ifdef V_HAVE_UTILS
  (void)sizeof(int);
#endif
#ifdef V_HAVE_UI
  (void)sizeof(int);
#endif
}
