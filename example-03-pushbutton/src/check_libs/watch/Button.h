#pragma once
#include_next <Button.h>
#include "../mark_use.hpp"
namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_BUTTON("Button.h"); } }; inline M _m; }
