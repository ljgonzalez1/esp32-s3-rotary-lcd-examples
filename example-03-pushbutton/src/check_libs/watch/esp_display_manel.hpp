#pragma once
#include_next <esp_display_panel.hpp>
#include "../mark_use.hpp"
namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_PANEL("esp_display_panel.hpp"); } }; inline M _m; }
