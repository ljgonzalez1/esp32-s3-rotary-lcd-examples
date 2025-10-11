#pragma once
#include_next <esp_lib_utils.h>
#include "../mark_use.hpp"
namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_UTILS("esp_lib_utils.h"); } }; inline M _m; }
