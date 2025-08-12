#include <Arduino.h>
#include "serial_prompt.h"

#ifndef USB_MONITOR_BAUD
#define USB_MONITOR_BAUD 115200
#endif

static void banner(const char* msg) {
  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(msg);
  Serial.println(F("=================================================="));
}

static void printPrompt() {
  Serial.print(F("[user]: "));
  Serial.flush();
}

static char gLineBuf[256];
static SerialPrompt gPrompt(gLineBuf, sizeof(gLineBuf));

void setup() {
  Serial.begin(USB_MONITOR_BAUD);
  unsigned long t0 = millis();
  while (!Serial && (millis() - t0 < 3000)) { delay(50); }

  banner("==== Setup start ====");
  Serial.printf("USB CDC baud: %d\r\n", (int)USB_MONITOR_BAUD);
  Serial.println(F("Type a line and press Enter."));
  banner("==== Setup end ====");

  printPrompt();
}

void loop() {
  while (Serial.available() > 0) {
    int ch = Serial.read();
    if (ch < 0) break;

    bool done = false;
    char c = (char)ch;

    // Echo printable & backspace to terminal for immediate feedback
    if (c == '\b' || (uint8_t)c == 127) {
      // emit terminal erase only if something to erase
      if (gPrompt.len > 0) Serial.print("\b \b");
    } else if ((uint8_t)c >= 32) {
      // printable characters echo
      Serial.write((uint8_t)c);
    }

    (void)gPrompt.feed(c, done);

    if (done) {
      const char* line = gPrompt.c_str();
      Serial.print("\r\n");
      Serial.println(make_response(line));
      printPrompt();
      gPrompt.reset();
    }
  }

  delay(30);
}
