/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>

HLIB_BEGIN()

// 8-bit integer type (-128 to 127)
using i8  = HLIB_STATIC_TYPE_8BIT;
// 16-bit integer type (-32768 to 32767)
using i16 = HLIB_STATIC_TYPE_16BIT;
// 32-bit integer type (-2147483648 to 2147483647)
using i32 = HLIB_STATIC_TYPE_32BIT;
// 64-bit integer type (-9223372036854775808 to 9223372036854775807)
using i64 = HLIB_STATIC_TYPE_64BIT;

// unsigned(zero and above) 8-bit integer type (0 to 255)
using u8  = unsigned HLIB_STATIC_TYPE_8BIT;
// unsigned(zero and above) 16-bit integer type (0 to 65535)
using u16 = unsigned HLIB_STATIC_TYPE_16BIT;
// unsigned(zero and above) 32-bit integer type (0 to 4294967295)
using u32 = unsigned HLIB_STATIC_TYPE_32BIT;
// unsigned(zero and above) 64-bit integer type (0 to 18446744073709551615)
using u64 = unsigned HLIB_STATIC_TYPE_64BIT;

using size_t = HLIB_SIZE_TYPE;
using ptrdiff_t = HLIB_PTRDIFF_TYPE;
using intptr_t = HLIB_INTPTR_TYPE;

using nullptr_t = HLIB_BULLPTR_TYPE;

HLIB_END()
