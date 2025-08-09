#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Serial.println("--- ESP32-S3 Specs ---");
  Serial.printf("Chip model     : %s\n",   ESP.getChipModel());
  Serial.printf("Chip revision  : %d\n",   ESP.getChipRevision());
  Serial.printf("CPU freq (MHz) : %d\n",   ESP.getCpuFreqMHz());
  Serial.printf("Cores          : %d\n",   ESP.getChipCores());

  uint32_t flash_bytes = ESP.getFlashChipSize();
  Serial.printf("Flash size     : %u MB\n", flash_bytes / (1024 * 1024));
  Serial.printf("Flash speed    : %u Hz\n", ESP.getFlashChipSpeed());

  bool has_psram = psramFound();
  Serial.printf("PSRAM present  : %s\n", has_psram ? "YES" : "NO");
  Serial.printf("PSRAM size     : %u MB\n", ESP.getPsramSize() / (1024 * 1024));
  Serial.println("-----------------------");
}

void loop() { delay(1000); }
