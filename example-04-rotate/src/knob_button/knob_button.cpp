#include "knob_button.hpp"

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

static const char* TAG = "knob_button";

namespace {
  struct ButtonEvent {
    uint32_t tick;
    uint8_t level; // 0 = pressed (active-low), 1 = released
  };

  static gpio_num_t s_pin = GPIO_NUM_NC;
  static QueueHandle_t s_queue = nullptr;

  static void IRAM_ATTR isr_handler(void*) {
    if (s_queue == nullptr) return;

    const int level = gpio_get_level(s_pin);
    ButtonEvent ev {
      .tick  = static_cast<uint32_t>(xTaskGetTickCountFromISR()),
      .level = static_cast<uint8_t>(level ? 1 : 0),
    };

    BaseType_t hp_task_woken = pdFALSE;
    (void)xQueueSendFromISR(s_queue, &ev, &hp_task_woken);
    if (hp_task_woken == pdTRUE) {
      portYIELD_FROM_ISR();
    }
  }

  static void button_task(void*) {
    // Debounce simple por tiempo entre eventos
    const TickType_t debounce_ticks = pdMS_TO_TICKS(30);

    ButtonEvent ev {};
    uint32_t last_tick = 0xFFFFFFFFu;

    while (true) {
      if (xQueueReceive(s_queue, &ev, portMAX_DELAY) != pdTRUE) continue;

      if (last_tick != 0xFFFFFFFFu) {
        const uint32_t dt = ev.tick - last_tick;
        if (dt < static_cast<uint32_t>(debounce_ticks)) {
          continue; // rebote
        }
      }
      last_tick = ev.tick;

      // En este módulo el botón es active-low (típico con pull-up)
      if (ev.level == 0) {
        ESP_LOGI(TAG, "Button pressed down (GPIO%d)", static_cast<int>(s_pin));
      } else {
        ESP_LOGI(TAG, "Button released (GPIO%d)", static_cast<int>(s_pin));
      }
    }
  }
} // namespace

void knob_button_start(gpio_num_t pin) {
  s_pin = pin;

  if (s_queue == nullptr) {
    s_queue = xQueueCreate(16, sizeof(ButtonEvent));
  }
  if (s_queue == nullptr) {
    ESP_LOGE(TAG, "Failed to create queue");
    return;
  }

  // Config GPIO input con pull-up y ambos flancos
  gpio_config_t cfg = {};
  cfg.intr_type = GPIO_INTR_ANYEDGE;
  cfg.mode = GPIO_MODE_INPUT;
  cfg.pin_bit_mask = 1ULL << static_cast<int>(s_pin);
  cfg.pull_up_en = GPIO_PULLUP_ENABLE;
  cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;

  const esp_err_t cfg_err = gpio_config(&cfg);
  if (cfg_err != ESP_OK) {
    ESP_LOGE(TAG, "gpio_config failed: %s", esp_err_to_name(cfg_err));
    return;
  }

  // ISR service (si ya está instalado, no es error fatal)
  esp_err_t isr_err = gpio_install_isr_service(0);
  if (isr_err != ESP_OK && isr_err != ESP_ERR_INVALID_STATE) {
    ESP_LOGE(TAG, "gpio_install_isr_service failed: %s", esp_err_to_name(isr_err));
    return;
  }

  gpio_isr_handler_remove(s_pin);
  const esp_err_t add_err = gpio_isr_handler_add(s_pin, &isr_handler, nullptr);
  if (add_err != ESP_OK) {
    ESP_LOGE(TAG, "gpio_isr_handler_add failed: %s", esp_err_to_name(add_err));
    return;
  }

  // Task que imprime por serial
  static constexpr uint32_t stack_words = 4096;
  const BaseType_t ok = xTaskCreate(button_task, "knob_button", stack_words, nullptr, 10, nullptr);
  if (ok != pdPASS) {
    ESP_LOGE(TAG, "xTaskCreate failed");
    return;
  }

  ESP_LOGI(TAG, "Knob button started on GPIO%d (active-low)", static_cast<int>(s_pin));
}
