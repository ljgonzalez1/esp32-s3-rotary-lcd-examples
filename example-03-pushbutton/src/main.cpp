// src/main.cpp  (ESP-IDF puro en C++)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "check_libs/marks.cpp"

extern "C" void app_main(void) {
  vuewe_show_imported_libs();

  while (true) {
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
