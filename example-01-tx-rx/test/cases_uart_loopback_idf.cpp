#include <Arduino.h>
#include <unity.h>
#include "driver/uart.h"

void test_uart1_loopback_idf() {
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

  // loopback interno (sin cables)
  TEST_ASSERT_EQUAL(ESP_OK, uart_set_loop_back(PORT, true));

  const char* msg = "PING-123";
  const int   len = strlen(msg);
  TEST_ASSERT_EQUAL(len, uart_write_bytes(PORT, msg, len));

  uint8_t rx[16] = {0};
  int rd = uart_read_bytes(PORT, rx, len, pdMS_TO_TICKS(500));
  TEST_ASSERT_EQUAL(len, rd);
  TEST_ASSERT_EQUAL_MEMORY(msg, rx, len);

  (void)uart_set_loop_back(PORT, false);
  uart_driver_delete(PORT);
}
