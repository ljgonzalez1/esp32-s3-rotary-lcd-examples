#include <cstdio>
#include "esp_log.h"

#include "check_libs.hpp"
#include "marks.hpp"

static const char* TAG = "libs_import_info";

static void banner(const char* msg) {
  std::printf("\n==================================================\n");
  std::printf("%s\n", msg);
  std::printf("==================================================\n");
}
static void report_line(const char* name, bool imported, const char* hdr) {
  if (imported) {
    ESP_LOGI(TAG, "[  IMPORTED  ] %-20s <%s>", name, (hdr? hdr : "?"));
  } else {
    ESP_LOGW(TAG, "[  --------  ] %-20s (header not found or not used)", name);
  }
}

void viewe_show_imported_libs(void) {
  banner("VIEWE libs import check");

  report_line("LVGL",                viewe::imports::lvgl.load(),   viewe::imports::lvgl_hdr);
  report_line("ESP32_Display_Panel", viewe::imports::panel.load(),  viewe::imports::panel_hdr);
  report_line("ESP32_IO_Expander",   viewe::imports::iox.load(),    viewe::imports::iox_hdr);
  report_line("ESP32_Button",        viewe::imports::button.load(), viewe::imports::button_hdr);
  report_line("ESP32_Knob",          viewe::imports::knob.load(),   viewe::imports::knob_hdr);
  report_line("esp-lib-utils",       viewe::imports::utils.load(),  viewe::imports::utils_hdr);
  report_line("ui (SquareLine)",     viewe::imports::ui.load(),     viewe::imports::ui_hdr);

  std::printf("\nAll modules listed based on actual includes.\n");
}
