#pragma once

#include <atomic>

namespace viewe::imports {
  // "Is library being used?" marker
  inline std::atomic<bool> lvgl   {false};
  inline std::atomic<bool> panel  {false};
  inline std::atomic<bool> iox    {false};
  inline std::atomic<bool> button {false};
  inline std::atomic<bool> knob   {false};
  inline std::atomic<bool> utils  {false};
  inline std::atomic<bool> ui     {false};

  // Header location
  inline const char* lvgl_hdr =   nullptr;
  inline const char* panel_hdr =  nullptr;
  inline const char* iox_hdr =    nullptr;
  inline const char* button_hdr = nullptr;
  inline const char* knob_hdr =   nullptr;
  inline const char* utils_hdr =  nullptr;
  inline const char* ui_hdr =     nullptr;
}
