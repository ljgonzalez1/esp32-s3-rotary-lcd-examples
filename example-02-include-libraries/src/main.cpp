// src/main.cpp  (ESP-IDF puro en C++)
#include "libs_import.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <cstdio>

static const char* TAG = "libs_import_check";

static void banner(const char* msg) {
  std::printf("\n==================================================\n");
  std::printf("%s\n", msg);
  std::printf("==================================================\n");
}

static void report(const char* name, const char* hdr, bool ok) {
  if (ok) {
    ESP_LOGI(TAG, "[OK] %s  <%s>", name, hdr);
  } else {
    ESP_LOGW(TAG, "[--] %s  (header not found)", name);
  }
}

// ⚠️ En C++ el punto de entrada debe tener *enlace C*
extern "C" void app_main(void) {
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

#if V_HAVE_BTN
  report("ESP32_Button", V_BTN_HDR, true);
#else
  report("ESP32_Button", "", false);
#endif

#if V_HAVE_KNOB
  report("ESP32_Knob", V_KNOB_HDR, true);
#else
  report("ESP32_Knob", "", false);
#endif

#if V_HAVE_UTILS
  report("esp-lib-utils", V_UTILS_HDR, true);
#else
  report("esp-lib-utils", "", false);
#endif

#if V_HAVE_UI
  report("ui (SquareLine)", V_UI_HDR, true);
#else
  report("ui (SquareLine)", "", false);
#endif

  viewe_touch_symbols_minimal();

  std::printf("\nAll modules included (where headers were found).\n");

  // Reemplazo del loop() de Arduino
  while (true) {
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
