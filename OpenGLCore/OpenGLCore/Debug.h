#pragma once

#include <intrin.h>

#define DBG_ASSERT(f) { if (f != 0) { __debugbreak(); } }
#define DBG_ASSERT_NAN(f) { if (f != f) { __debugbreak(); } }