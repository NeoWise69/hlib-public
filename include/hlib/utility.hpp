/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <traits.hpp>

HLIB_BEGIN()

template<class T>
static inline T&& forward(typename remove_reference<T>::type& parameter) HLIB_NOEXCEPT;

#include <details/utility.inl>

HLIB_END()
