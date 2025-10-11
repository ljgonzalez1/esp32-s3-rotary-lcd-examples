#pragma once
#include_next <Knob.h>
#include "../mark_use.hpp"
namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_KNOB("Knob.h"); } }; inline M _m; }
