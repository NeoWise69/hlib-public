/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>
#include <int.hpp>

HLIB_BEGIN()

_HLIB void*
malloc(size_t size);

_HLIB void
free(void* block);

HLIB_END()
