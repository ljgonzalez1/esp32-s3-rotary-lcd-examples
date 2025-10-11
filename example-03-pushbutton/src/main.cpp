#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "check_libs/check_libs.hpp"

extern "C" [[noreturn]] void app_main(void) {
  viewe_show_imported_libs();

  while (true) {
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
