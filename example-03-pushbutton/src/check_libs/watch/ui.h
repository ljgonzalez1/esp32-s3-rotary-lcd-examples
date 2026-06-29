#pragma once
#include_next <ui.h>
#include "../mark_use.hpp"
namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_UI("ui.h"); } }; inline M _m; }
