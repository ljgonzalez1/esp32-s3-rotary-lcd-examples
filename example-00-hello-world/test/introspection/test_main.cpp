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
  TEST_ASSERT_TRUE_MESSAGE(f == 80 || f == 160 || f == 240, "CPU freq debe ser 80/160/240 MHz");
}

void test_flash_size() {
  size_t fs = ESP.getFlashChipSize();
  TEST_ASSERT_TRUE_MESSAGE(fs >= (8u * 1024u * 1024u), "Flash debe ser >= 8 MiB");
}

void test_psram() {
  TEST_ASSERT_TRUE_MESSAGE(psramFound(), "PSRAM no detectada");
  TEST_ASSERT_TRUE_MESSAGE(ESP.getPsramSize() >= (8u * 1024u * 1024u), "PSRAM < 8 MiB");
}

void test_mac_format() {
  String mac = WiFi.macAddress();
  TEST_ASSERT_EQUAL(17, mac.length());           // "AA:BB:CC:DD:EE:FF"
  TEST_ASSERT_EQUAL(':', mac.charAt(2));
  TEST_ASSERT_NOT_EQUAL(0, mac.compareTo("00:00:00:00:00:00"));
}

void test_partitions_alignment_and_running() {
  // Todas las particiones deben estar alineadas a 0x1000 y con tamaño múltiplo de 0x1000
  esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  int count = 0;
  while (it) {
    const esp_partition_t* p = esp_partition_get(it);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, p->address & 0xFFF, "Offset no alineado");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, p->size    & 0xFFF, "Size no alineado");
    count++;
    it = esp_partition_next(it);
  }
  esp_partition_iterator_release(it);
  TEST_ASSERT_TRUE_MESSAGE(count > 0, "Sin particiones?");
  // Debe existir partición en ejecución
  const esp_partition_t* running = esp_ota_get_running_partition();
  TEST_ASSERT_NOT_NULL_MESSAGE(running, "Sin partición running");
}

void test_otadata_size_if_present() {
  // Si hay otadata, su tamaño debe ser 0x2000
  const esp_partition_t* ota =
      esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_OTA, NULL);
  if (ota) {
    TEST_ASSERT_EQUAL_UINT32(0x2000, ota->size);
  } else {
    TEST_IGNORE_MESSAGE("Sin partición otadata (OK si usas solo 'factory')");
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

void loop() {}

