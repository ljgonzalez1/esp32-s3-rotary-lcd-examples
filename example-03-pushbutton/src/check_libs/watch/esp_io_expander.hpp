#pragma once
#include_next <esp_io_expander.hpp>
#include "../mark_use.hpp"
namespace viewe::auto_mark { struct M { M(){ VIEWE_MARK_IOX("esp_io_expander.hpp"); } }; inline M _m; }
