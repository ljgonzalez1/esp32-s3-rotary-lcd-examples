#include <Arduino.h>
#include <unity.h>
#include "driver/uart.h"

static void wait_serial2() {
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(10); }
}

void test_uart1_loopback_idf() {
  // Configure UART1 via ESP-IDF driver and enable internal loopback
  const uart_port_t PORT = UART_NUM_1;
  uart_config_t cfg = {};
  cfg.baud_rate = 115200;
  cfg.data_bits = UART_DATA_8_BITS;
  cfg.parity    = UART_PARITY_DISABLE;
  cfg.stop_bits = UART_STOP_BITS_1;
  cfg.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
#if ESP_IDF_VERSION_MAJOR >= 5
  cfg.source_clk = UART_SCLK_DEFAULT;
#else
  cfg.source_clk = UART_SCLK_APB;
#endif

  TEST_ASSERT_EQUAL(ESP_OK, uart_param_config(PORT, &cfg));
  TEST_ASSERT_EQUAL(ESP_OK, uart_set_pin(PORT, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE,
                                         UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  TEST_ASSERT_EQUAL(ESP_OK, uart_driver_install(PORT, 256, 256, 0, NULL, 0));

  // Enable internal loopback (no external wiring needed)
#ifdef UART_LOOPBACK
  TEST_ASSERT_EQUAL(ESP_OK, uart_set_loop_back(PORT, true));
#else
  // Some IDF variants gate this behind same API; still try
  TEST_ASSERT_EQUAL(ESP_OK, uart_set_loop_back(PORT, true));
#endif

  const char* msg = "PING-123";
  const int   len = strlen(msg);
  TEST_ASSERT_EQUAL(len, uart_write_bytes(PORT, msg, len));

  uint8_t rx[16] = {0};
  int rd = uart_read_bytes(PORT, rx, len, pdMS_TO_TICKS(500));
  TEST_ASSERT_EQUAL(len, rd);
  TEST_ASSERT_EQUAL_MEMORY(msg, rx, len);

  // Cleanup
  (void)uart_set_loop_back(PORT, false);
  uart_driver_delete(PORT);
}

void setUp2() {}
void tearDown2() {}

void setup() {
  wait_serial2();
  UNITY_BEGIN();
  RUN_TEST(test_uart1_loopback_idf);
  UNITY_END();
}

void loop() { delay(1000); }
