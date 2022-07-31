/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>
#include <int.hpp>
#include <memory/malloc.hpp>

HLIB_BEGIN()

// Default and simpliest allocator type
struct static_allocator {
	static void* allocate(size_t bytes) HLIB_NOEXCEPT;
	static void  deallocate(void* ptr, size_t /*bytes*/) HLIB_NOEXCEPT;
};

#include <details/static_allocator.inl>

#define HLIB_STATIC_ALLOCATOR ::hlib::static_allocator

HLIB_END()
