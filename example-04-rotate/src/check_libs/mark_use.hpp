#pragma once

#ifdef __cplusplus
  #include "marks.hpp"

  namespace viewe::imports {
    inline void mark_lvgl (const char* hdr){ lvgl.store(true,  std::memory_order_relaxed); lvgl_hdr  = hdr; }
    inline void mark_panel(const char* hdr){ panel.store(true, std::memory_order_relaxed); panel_hdr = hdr; }
    inline void mark_iox  (const char* hdr){ iox.store(true,   std::memory_order_relaxed); iox_hdr   = hdr; }
    inline void mark_button(const char* hdr){ button.store(true,std::memory_order_relaxed); button_hdr= hdr; }
    inline void mark_knob (const char* hdr){ knob.store(true,  std::memory_order_relaxed); knob_hdr  = hdr; }
    inline void mark_utils(const char* hdr){ utils.store(true, std::memory_order_relaxed); utils_hdr = hdr; }
    inline void mark_ui   (const char* hdr){ ui.store(true,    std::memory_order_relaxed); ui_hdr    = hdr; }
  }

// (Opcional) Aliases para compatibilidad con el nombre que proponías
inline void viewe_mark_lvgl (const char* hdr){ viewe::imports::mark_lvgl(hdr);  }
inline void viewe_mark_panel(const char* hdr){ viewe::imports::mark_panel(hdr); }
inline void viewe_mark_iox  (const char* hdr){ viewe::imports::mark_iox(hdr);   }
inline void viewe_mark_button(const char* hdr){viewe::imports::mark_button(hdr);}
inline void viewe_mark_knob (const char* hdr){ viewe::imports::mark_knob(hdr);  }
inline void viewe_mark_utils(const char* hdr){ viewe::imports::mark_utils(hdr); }
inline void viewe_mark_ui   (const char* hdr){ viewe::imports::mark_ui(hdr);    }

#else
/* Compilación C: NO hacer nada (evita que TUs C fallen) */
#define viewe_mark_lvgl(h)    ((void)0)
#define viewe_mark_panel(h)   ((void)0)
#define viewe_mark_iox(h)     ((void)0)
#define viewe_mark_button(h)  ((void)0)
#define viewe_mark_knob(h)    ((void)0)
#define viewe_mark_utils(h)   ((void)0)
#define viewe_mark_ui(h)      ((void)0)
#endif
