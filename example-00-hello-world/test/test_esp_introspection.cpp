#include <Arduino.h>
#include <unity.h>

#include "esp_system.h"
#include "esp_ota_ops.h"
#include "esp_partition.h"
#include <WiFi.h>

static void wait_serial() {
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(10); }
}

/********* TESTS *********/

void test_cpu_freq() {
  auto f = ESP.getCpuFreqMHz();
  TEST_ASSERT_TRUE_MESSAGE(f == 80 || f == 160 || f == 240, "CPU frequency must be 80/160/240 MHz");
}

void test_flash_size() {
  size_t fs = ESP.getFlashChipSize();
  TEST_ASSERT_TRUE_MESSAGE(fs >= (8u * 1024u * 1024u), "Flash must be >= 8 MiB");
}

void test_psram() {
  TEST_ASSERT_TRUE_MESSAGE(psramFound(), "PSRAM not detected");
  TEST_ASSERT_TRUE_MESSAGE(ESP.getPsramSize() >= (8u * 1024u * 1024u - 4u * 1024u), "PSRAM >= 7.99609375 MiB");
}

void test_mac_format() {
  String mac = WiFi.macAddress();
  TEST_ASSERT_EQUAL(17, mac.length());           // "AA:BB:CC:DD:EE:FF"
  TEST_ASSERT_EQUAL(':', mac.charAt(2));
  TEST_ASSERT_NOT_EQUAL(0, mac.compareTo("00:00:00:00:00:00"));
}

void test_partitions_alignment_and_running() {
  // All partitions must be aligned to 0x1000 and have size multiple of 0x1000
  esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  int count = 0;
  while (it) {
    const esp_partition_t* p = esp_partition_get(it);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, p->address & 0xFFF, "Offset not aligned");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, p->size    & 0xFFF, "Size not aligned");
    count++;
    it = esp_partition_next(it);
  }
  esp_partition_iterator_release(it);
  TEST_ASSERT_TRUE_MESSAGE(count > 0, "No partitions found?");
  // Running partition must exist
  const esp_partition_t* running = esp_ota_get_running_partition();
  TEST_ASSERT_NOT_NULL_MESSAGE(running, "No running partition");
}

void test_otadata_size_if_present() {
  // If otadata exists, its size must be 0x2000
  const esp_partition_t* ota =
      esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_OTA, NULL);
  if (ota) {
    TEST_ASSERT_EQUAL_UINT32(0x2000, ota->size);
  } else {
    TEST_IGNORE_MESSAGE("No otadata partition (OK if using only 'factory')");
  }
}

/********* RUNNER *********/

void setUp() {}
void tearDown() {}

void setup() {
  wait_serial();
  delay(300);
  UNITY_BEGIN();
  RUN_TEST(test_cpu_freq);
  RUN_TEST(test_flash_size);
  RUN_TEST(test_psram);
  RUN_TEST(test_mac_format);
  RUN_TEST(test_partitions_alignment_and_running);
  RUN_TEST(test_otadata_size_if_present);
  UNITY_END();
}

void loop() {
  delay(1000);
}
