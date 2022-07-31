/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>

HLIB_BEGIN()

/* 
 Computes the absolute value of an numeric type value.
 The behavior is undefined if the result cannot be represented by the return type.
*/
template<class T>
T abs(T value);

#include <details/operations.inl>

HLIB_END()
