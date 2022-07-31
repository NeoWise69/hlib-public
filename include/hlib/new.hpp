/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>
#include <int.hpp>

HLIB_BEGIN()

// Literally 'new' placeholder
struct placeholder {};

HLIB_END()

_HLIB void* operator new(hlib::size_t, hlib::placeholder, void* ptr);

_HLIB void  operator delete(void*, hlib::placeholder, void* ptr) HLIB_THROW();

#include <details/new.inl>
