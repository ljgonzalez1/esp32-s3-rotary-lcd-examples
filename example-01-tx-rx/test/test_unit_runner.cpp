#include <Arduino.h>
#include <unity.h>

// prototipos de los casos, implementados en otros .cpp
void test_make_response_header();
void test_parser_crlf_single_line();
void test_parser_lf_only();
void test_parser_cr_only();
void test_parser_backspace();
void test_uart1_loopback_idf();

static void wait_serial() {
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(10); }
}

void setUp() {}
void tearDown() {}

void setup() {
  wait_serial();
  UNITY_BEGIN();

  // parser / header
  RUN_TEST(test_make_response_header);
  RUN_TEST(test_parser_crlf_single_line);
  RUN_TEST(test_parser_lf_only);
  RUN_TEST(test_parser_cr_only);
  RUN_TEST(test_parser_backspace);

  // TX/RX (loopback por driver IDF)
  RUN_TEST(test_uart1_loopback_idf);

  UNITY_END();
}
void loop() { delay(1000); }
