#pragma once
#include_next <lvgl.h>
#include "../mark_use.hpp"

namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_LVGL("lvgl.h"); } }; inline M _m; }
