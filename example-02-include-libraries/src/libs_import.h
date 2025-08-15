#pragma once

/* Helpers para imprimir qué header se tomó */
#ifndef V_STR
#  define V_XSTR(x) #x
#  define V_STR(x)  V_XSTR(x)
#endif

/* ========= LVGL ========= */
#if __has_include(<lvgl.h>)
#  include <lvgl.h>
#  define V_HAVE_LVGL 1
#  define V_LVGL_HDR  "lvgl.h"
#elif __has_include(<lvgl/lvgl.h>)
#  include <lvgl/lvgl.h>
#  define V_HAVE_LVGL 1
#  define V_LVGL_HDR  "lvgl/lvgl.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/lvgl-release-v8.4/lvgl.h")
#  include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/lvgl-release-v8.4/lvgl.h"
#  define V_HAVE_LVGL 1
#  define V_LVGL_HDR  "third_party/.../lvgl-release-v8.4/lvgl.h"
#endif

/* ===== ESP32_Display_Panel =====
   Nota: en la práctica aparecen ambas variantes:
   - <esp_panel_library.h>  (minúsculas)
   - <ESP_Panel_Library.h>  (CamelCase, usado en ejemplos Arduino)
   y también el wrapper C++ moderno <esp_display_panel.hpp>.
*/
#ifndef V_HAVE_PANEL
#  define V_HAVE_PANEL 0
#  define V_PANEL_HDR  ""
#endif

#if __has_include(<esp_panel_library.h>)
#  undef  V_HAVE_PANEL
#  undef  V_PANEL_HDR
#  define V_HAVE_PANEL 1
#  define V_PANEL_HDR  "esp_panel_library.h"
#  include <esp_panel_library.h>
#elif __has_include(<ESP_Panel_Library.h>)
#  undef  V_HAVE_PANEL
#  undef  V_PANEL_HDR
#  define V_HAVE_PANEL 1
#  define V_PANEL_HDR  "ESP_Panel_Library.h"
#  include <ESP_Panel_Library.h>
#elif __has_include(<esp_display_panel.hpp>)
#  undef  V_HAVE_PANEL
#  undef  V_PANEL_HDR
#  define V_HAVE_PANEL 1
#  define V_PANEL_HDR  "esp_display_panel.hpp"
#  include <esp_display_panel.hpp>
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Display_Panel/src/esp_panel_library.h")
#  undef  V_HAVE_PANEL
#  undef  V_PANEL_HDR
#  define V_HAVE_PANEL 1
#  define V_PANEL_HDR  "third_party/.../ESP32_Display_Panel/src/esp_panel_library.h"
#  include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Display_Panel/src/esp_panel_library.h"
#endif

/* --- ESP32_IO_Expander --- */
#undef V_HAVE_IOX
#undef V_IOX_HDR
#if __has_include(<esp_io_expander.hpp>)
#  define V_HAVE_IOX 1
#  define V_IOX_HDR "esp_io_expander.hpp"
#  include <esp_io_expander.hpp>
#else
#  define V_HAVE_IOX 0
#  define V_IOX_HDR ""
#endif

/* ===== ESP32_Button ===== */
#if __has_include(<Button.h>)
#  include <Button.h>
#  define V_HAVE_BTN 1
#  define V_BTN_HDR "Button.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Button/src/Button.h")
#  include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Button/src/Button.h"
#  define V_HAVE_BTN 1
#  define V_BTN_HDR "third_party/.../ESP32_Button/src/Button.h"
#endif

/* ===== ESP32_Knob ===== */
#if __has_include(<ESP_Knob.h>)
#  include <ESP_Knob.h>
#  define V_HAVE_KNOB 1
#  define V_KNOB_HDR "ESP_Knob.h"
#elif __has_include(<Knob.h>)
#  include <Knob.h>
#  define V_HAVE_KNOB 1
#  define V_KNOB_HDR "Knob.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Knob/src/ESP_Knob.h")
#  include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ESP32_Knob/src/ESP_Knob.h"
#  define V_HAVE_KNOB 1
#  define V_KNOB_HDR "third_party/.../ESP32_Knob/src/ESP_Knob.h"
#endif

/* ===== esp-lib-utils ===== (cabecera canónica: esp_lib_utils.h) */
#ifndef V_HAVE_UTILS
#  define V_HAVE_UTILS 0
#endif
#ifndef V_UTILS_HDR
#  define V_UTILS_HDR ""
#endif

#if __has_include(<esp_lib_utils.h>)
#  undef  V_HAVE_UTILS
#  undef  V_UTILS_HDR
#  define V_HAVE_UTILS 1
#  define V_UTILS_HDR "esp_lib_utils.h"
#  include <esp_lib_utils.h>
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/esp-lib-utils/src/esp_lib_utils.h")
#  undef  V_HAVE_UTILS
#  undef  V_UTILS_HDR
#  define V_HAVE_UTILS 1
#  define V_UTILS_HDR "third_party/.../esp-lib-utils/src/esp_lib_utils.h"
#  include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/esp-lib-utils/src/esp_lib_utils.h"
#endif

/* ===== ui (SquareLine) ===== */
#if __has_include(<ui.h>)
#  include <ui.h>
#  define V_HAVE_UI 1
#  define V_UI_HDR "ui.h"
#elif __has_include("third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ui/ui.h")
#  include "third_party/viewesmart-md80esp32-knob-2.1inch-fork/Libraries/ui/ui.h"
#  define V_HAVE_UI 1
#  define V_UI_HDR "third_party/.../ui/ui.h"
#endif

/* “Tocar” símbolos mínimos para que el linker coja las unidades */
inline void viewe_touch_symbols_minimal() {
#if V_HAVE_LVGL
  lv_init(); // seguro sin drivers
#endif
#if defined(V_HAVE_BTN)
  (void)sizeof(Button);
#endif
#if defined(V_HAVE_KNOB)
  (void)sizeof(ESP_Knob);
#endif
#if V_HAVE_IOX
  using _iox_anchor_t = esp_expander::Base;
  (void)sizeof(_iox_anchor_t);
#endif
#if V_HAVE_PANEL
  /* Alias antiguo (deprecado) que algunas variantes aún exportan */
# ifdef ESP_Panel
  (void)sizeof(ESP_Panel);
# endif
#endif
#if V_HAVE_UTILS
  (void)sizeof(int);
#endif
#if defined(V_HAVE_UI)
  (void)sizeof(int);
#endif
}
