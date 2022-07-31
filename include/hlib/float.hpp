/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>

HLIB_BEGIN()

// High precision floating point type
using real_t = double;
// Half precision floating point type
using half_t = float;

using f32 = half_t;
using f64 = real_t;

#define f32min (half_t)( 1.17549e-38 )
#define f32max (half_t)( 3.40282e+38 )
#define f32eps (half_t)( 1.19209e-07 )

#define f64min (real_t)( 2.22507e-308 )
#define f64max (real_t)( 1.79769e+308 )
#define f64eps (real_t)( 2.22045e-16 )

// Compare two halfs and return true if it is equals
_HLIB bool f32cmp(half_t v1, half_t v2); 

// Compare two reals and return true if it is equals
_HLIB bool f64cmp(real_t v1, real_t v2);

HLIB_END()
