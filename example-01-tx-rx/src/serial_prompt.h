#pragma once
#include <stddef.h>
#include <stdint.h>
#include <Arduino.h>

// Small line-editor state machine: feeds chars, detects end-of-line, handles CR/LF & backspace.
struct SerialPrompt {
  char*   buf;
  size_t  cap;
  size_t  len;
  bool    swallowLF; // if true, swallow next '\n' (we just saw a '\r')

  SerialPrompt(char* storage, size_t capacity)
      : buf(storage), cap(capacity), len(0), swallowLF(false) {}

  void reset() { len = 0; /* DON'T reset swallowLF here */ }

  // Feed one character. Returns true if consumed.
  // If this char completes a line, sets lineDone=true.
  bool feed(char c, bool& lineDone) {
    lineDone = false;

    if (c == '\r') {           // CR ends the line, swallow next LF
      swallowLF = true;
      lineDone = true;
      return true;
    }
    if (c == '\n') {           // LF ends the line (unless it's CRLF's LF)
      if (swallowLF) {
        swallowLF = false;
        return true;  // Don't set lineDone=true here, it was already set by '\r'
      }
      // Only treat standalone LF as line ending if we have content or it's truly standalone
      lineDone = true;
      return true;
    }

    // Reset swallowLF flag if we get any other character
    if (swallowLF) {
      swallowLF = false;
    }

    // Editing: backspace / delete
    if (c == '\b' || (uint8_t)c == 127) {
      if (len > 0) { len--; }
      return true;
    }

    // Ignore other control chars
    if ((uint8_t)c < 32) return true;

    // Append printable
    if (len < cap - 1) { buf[len++] = c; return true; }
    return false; // full
  }

  // Null-terminate in-place and return C string view of current line
  const char* c_str() {
    if (cap > 0) buf[len] = '\0';
    return buf;
  }
};

// Build the response line without printing (useful for tests and formatting)
inline String make_response(const char* msg) {
  String out(F("[esp32s3]: User said \""));
  out += msg;
  out += F("\"");
  return out;
}
