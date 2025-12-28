#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "check_libs/check_libs.hpp"
#include "config_pins.h"
#include "knob_button/knob_button.hpp"

extern "C" [[noreturn]] void app_main(void) {
  // Mantienes tu checker
  viewe_show_imported_libs();

  // Arrancas el botón (pulsación de la perilla)
  knob_button_start(PIN_SW);

  while (true) {
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}