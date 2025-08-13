#if !defined(PIO_UNIT_TESTING) && !defined(UNIT_TEST)

#include <Arduino.h>
#include "serial_prompt.h"

#ifndef USB_MONITOR_BAUD
#define USB_MONITOR_BAUD 115200
#endif

// -------- Constants --------
constexpr unsigned long IDLE_DELAY = 30;
constexpr size_t BUFFER_SIZE = 256;

// -------- Banner Management --------
class BannerManager {
public:
  static void showBanner(const char* msg) {
    Serial.println();
    Serial.println(F("=================================================="));
    Serial.println(msg);
    Serial.println(F("=================================================="));
  }

  static void showPrompt() {
    Serial.print(F("[user]: "));
    Serial.flush();
  }
};

// -------- Terminal Operations --------
class TerminalOperations {
public:
  static void echoCharacter(char c) {
    Serial.write(c);
  }

  static void performBackspace() {
    Serial.print(F("\b \b"));
  }

  static void ringBell() {
    Serial.write('\a');
  }

  static void showCompleteLine(const char* line) {
    Serial.print(F("\n"));
    Serial.print(make_response(line));
    Serial.println(F("\n"));
  }
};

// -------- Input Processor using SerialPrompt --------
class InputProcessor {
private:
  char buffer[BUFFER_SIZE];
  SerialPrompt prompt;

public:
  InputProcessor() : prompt(buffer, BUFFER_SIZE) {}

  void processAvailableInput() {
    while (Serial.available() > 0) {
      int ch = Serial.read();
      if (ch < 0) break;

      processCharacter(static_cast<char>(ch));
    }
  }

private:
  void processCharacter(char c) {
    bool lineDone = false;
    bool consumed = prompt.feed(c, lineDone);

    if (consumed) {
      // Handle character display/feedback
      if (c == '\b' || (uint8_t)c == 127) {
        // Backspace - only show feedback if character was actually removed
        TerminalOperations::performBackspace();
      } else if ((uint8_t)c >= 32) {
        // Printable character - echo it
        TerminalOperations::echoCharacter(c);
      }
      // Control characters and line endings are silently handled by SerialPrompt
    } else {
      // Buffer full - ring bell
      TerminalOperations::ringBell();
    }

    // Only handle complete line once, after SerialPrompt has processed it
    if (lineDone) {
      handleCompleteLine();
    }
  }

  void handleCompleteLine() {
    TerminalOperations::showCompleteLine(prompt.c_str());
    BannerManager::showPrompt();
    prompt.reset();
  }
};

// -------- System Initialization --------
class SystemInitializer {
public:
  static void initialize() {
    Serial.begin(USB_MONITOR_BAUD);
    waitForSerial();
    showStartupMessages();
  }

private:
  static void waitForSerial() {
    unsigned long t0 = millis();
    while (!Serial && (millis() - t0 < 3000)) {
      delay(50);
    }
  }

  static void showStartupMessages() {
    BannerManager::showBanner("==== Setup start ====");
    Serial.printf("USB CDC baud: %d", static_cast<int>(USB_MONITOR_BAUD));
    Serial.println();
    Serial.println(F("Type a line and press Enter."));
    BannerManager::showBanner("==== Setup end ====");
    BannerManager::showPrompt();
  }
};

// -------- Global Objects --------
static InputProcessor g_inputProcessor;

// -------- Arduino Entry Points --------
void setup() {
  SystemInitializer::initialize();
}

void loop() {
  g_inputProcessor.processAvailableInput();
  delay(IDLE_DELAY);
}

#endif
