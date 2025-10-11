#pragma once
#include_next <ESP_Knob.h>
#include "../mark_use.hpp"
namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_KNOB("ESP_Knob.h"); } }; inline M _m; }
