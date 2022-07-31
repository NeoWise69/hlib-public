/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <int.hpp>

HLIB_BEGIN()

// Returns hash-integer of the given string
_HLIB size_t strhash(const char* str_, size_t len);

// Templated hash function
template<class T>
inline size_t hash(const T& value);

#include <details/hash.inl>

HLIB_END()
