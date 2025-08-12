// File: src/main.cpp
// ESP32‑S3 Introspection Hello World (Arduino core 3.x compatible)
// setup(): imprime la mayor cantidad de info interna posible
// loop(): imprime "Hello, world!" cada 1 s

#include <Arduino.h>
#include <WiFi.h>

// ESP-IDF headers expuestos por Arduino-ESP32 3.x
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_ota_ops.h"
#include "esp_partition.h"

static const char* partTypeToStr(esp_partition_type_t t) {
  switch (t) {
    case ESP_PARTITION_TYPE_APP:  return "app";
    case ESP_PARTITION_TYPE_DATA: return "data";
    default: return "unknown";
  }
}

static String partSubTypeToStr(const esp_partition_t* p) {
  if (!p) return "?";
  if (p->type == ESP_PARTITION_TYPE_APP) {
    switch (p->subtype) {
      case ESP_PARTITION_SUBTYPE_APP_FACTORY: return "factory";
      case ESP_PARTITION_SUBTYPE_APP_OTA_0:   return "ota_0";
      case ESP_PARTITION_SUBTYPE_APP_OTA_1:   return "ota_1";
      case ESP_PARTITION_SUBTYPE_APP_OTA_2:   return "ota_2";
      case ESP_PARTITION_SUBTYPE_APP_OTA_3:   return "ota_3";
      case ESP_PARTITION_SUBTYPE_APP_OTA_4:   return "ota_4";
      case ESP_PARTITION_SUBTYPE_APP_OTA_5:   return "ota_5";
      case ESP_PARTITION_SUBTYPE_APP_OTA_6:   return "ota_6";
      case ESP_PARTITION_SUBTYPE_APP_OTA_7:   return "ota_7";
      default: return String("app_") + String(p->subtype, 10);
    }
  } else if (p->type == ESP_PARTITION_TYPE_DATA) {
    switch (p->subtype) {
      case ESP_PARTITION_SUBTYPE_DATA_NVS:    return "nvs";
      case ESP_PARTITION_SUBTYPE_DATA_PHY:    return "phy";
      case ESP_PARTITION_SUBTYPE_DATA_OTA:    return "ota";
      case ESP_PARTITION_SUBTYPE_DATA_SPIFFS: return "spiffs"; // también LittleFS
      case ESP_PARTITION_SUBTYPE_DATA_FAT:    return "fat";
      default: return String("data_") + String(p->subtype, 10);
    }
  }
  return "-";
}

static void printPartitionTable() {
  Serial.println("\n[Partitions]");
  Serial.printf("%-12s %-6s %-8s %-10s %-10s\n", "Label", "Type", "SubType", "Offset", "Size");

  esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  while (it) {
    const esp_partition_t* p = esp_partition_get(it);
    Serial.printf("%-12s %-6s %-8s 0x%08lx 0x%08lx\n",
                  p->label,
                  partTypeToStr(p->type),
                  partSubTypeToStr(p).c_str(),
                  (unsigned long)p->address,
                  (unsigned long)p->size);
    it = esp_partition_next(it);
  }
  esp_partition_iterator_release(it);

  const esp_partition_t* running = esp_ota_get_running_partition();
  const esp_partition_t* boot    = esp_ota_get_boot_partition();
  if (running) Serial.printf("Running app  : %s (0x%08lx)\n", running->label, (unsigned long)running->address);
  if (boot)    Serial.printf("Boot app set : %s (0x%08lx)\n", boot->label, (unsigned long)boot->address);
}

static void printData() {
  // --- Chip info ---
  esp_chip_info_t chipInfo; esp_chip_info(&chipInfo);
  uint32_t features = chipInfo.features;
  Serial.println("\n==== ESP32‑S3 Introspection ====");
  Serial.printf("Chip model     : %s\n", ESP.getChipModel());
  Serial.printf("Chip revision  : %d\n", ESP.getChipRevision());
  Serial.printf("Cores          : %d\n", chipInfo.cores);
  Serial.printf("Features       :%s%s%s\n",
                (features & CHIP_FEATURE_WIFI_BGN) ? " WiFi" : "",
                (features & CHIP_FEATURE_BLE)      ? " BLE"  : "",
                (features & CHIP_FEATURE_BT)       ? " BT"   : "");
  Serial.printf("CPU freq (MHz) : %u\n", ESP.getCpuFreqMHz());
  Serial.printf("SDK version    : %s\n", ESP.getSdkVersion());
  Serial.printf("Reset reason   : %d\n", (int)esp_reset_reason());

  // --- Flash info (compatibles con Arduino 3.x) ---
  size_t flashSize = ESP.getFlashChipSize();
  uint32_t flashSpeed = ESP.getFlashChipSpeed();
  Serial.printf("Flash size     : %u bytes (%.2f MB)\n", (unsigned)flashSize, flashSize/1024.0/1024.0);
  Serial.printf("Flash speed    : %u Hz\n", (unsigned)flashSpeed);
  // Modo de flash no se reporta en todas las versiones de Arduino; omitido para máxima compatibilidad.

  // --- PSRAM info ---
  Serial.printf("PSRAM present  : %s\n", psramFound() ? "yes" : "no");
  Serial.printf("PSRAM size     : %u bytes\n", (unsigned)ESP.getPsramSize());
  Serial.printf("PSRAM free     : %u bytes\n", (unsigned)ESP.getFreePsram());

  // --- Heap info ---
  Serial.printf("Heap size      : %u bytes\n", (unsigned)ESP.getHeapSize());
  Serial.printf("Heap free      : %u bytes\n", (unsigned)ESP.getFreeHeap());
  Serial.printf("Heap min free  : %u bytes\n", (unsigned)ESP.getMinFreeHeap());
  Serial.printf("Heap max alloc : %u bytes\n", (unsigned)ESP.getMaxAllocHeap());

  // --- Sketch sizes ---
  Serial.printf("Sketch size    : %u bytes\n", (unsigned)ESP.getSketchSize());
  Serial.printf("Free sketch    : %u bytes\n", (unsigned)ESP.getFreeSketchSpace());

  // --- MAC addresses ---
  String mac = WiFi.macAddress();
  Serial.printf("MAC WiFi STA   : %s\n", mac.c_str());

  // --- Partition table ---
  printPartitionTable();

  Serial.println("==== Setup done ====\n");
}

#ifndef UNIT_TEST
void setup() {
  delay(250);
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(100); }

  delay(1000);

  Serial.println("\n\n\n\n==== Setup started ====\n");
  printData();

}

void loop() {
  //static uint32_t n = 0;
  //Serial.printf("Hello, world! %lu\n", (unsigned long)n++);
  delay(1000);
}
#endif
