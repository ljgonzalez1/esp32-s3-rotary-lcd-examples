// File: src/main.cpp
// ESP32‑S3 — Serial prompt + echo
// Behavior:
//   - On boot, prints banners "Setup start" / "Setup end".
//   - Shows prompt: [user]:
//   - Reads a line from USB Serial (terminated by Enter / CR or LF).
//   - Replies: [esp32s3]: User said "<msg>"\r\n and reprints the prompt.
// Notes:
//   - Non-blocking loop with a small delay (~30 ms) to avoid busy-waiting.
//   - Handles CR, LF, CRLF, backspace and simple line editing.

#include <Arduino.h>

#ifndef USB_MONITOR_BAUD
#define USB_MONITOR_BAUD 115200
#endif

// -------- banners --------
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

// -------- line buffer --------
static char  lineBuf[256];
static size_t lineLen = 0;
static bool   lastWasCR = false; // to swallow LF after CR in CRLF sequences

static void resetLine() {
  lineLen = 0;
  lastWasCR = false;
}

static void handleCompleteLine() {
  lineBuf[lineLen] = '\0';
  Serial.print(F("\r\n[esp32s3]: User said \""));
  Serial.print(lineBuf);
  Serial.println(F("\""));
  printPrompt();
  resetLine();
}

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
  // drain all available characters this cycle
  while (Serial.available() > 0) {
    int ch = Serial.read();
    if (ch < 0) break;
    char c = (char)ch;

    // normalize CR/LF handling
    if (c == '\r') {
      lastWasCR = true;
      handleCompleteLine();
      continue;
    }
    if (c == '\n') {
      if (lastWasCR) {
        // part of CRLF -> already handled
        lastWasCR = false;
        continue;
      }
      handleCompleteLine();
      continue;
    }
    lastWasCR = false;

    // handle backspace / delete
    if (c == '\b' || c == 127) {
      if (lineLen > 0) {
        lineLen--;
        // Erase on terminal: back, space, back
        Serial.print("\b \b");
      }
      continue;
    }

    // basic printable range guard
    if ((uint8_t)c < 32) {
      // ignore other control chars
      continue;
    }

    if (lineLen < sizeof(lineBuf) - 1) {
      lineBuf[lineLen++] = c;
      Serial.write(c); // local echo
    } else {
      // buffer full: optionally beep or drop chars; here we drop with a bell
      Serial.write('\a');
    }
  }

  // small idle to avoid saturating CPU/USB
  delay(30);
}
