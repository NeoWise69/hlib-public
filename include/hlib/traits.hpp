/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <new.hpp>

#if MACRO_TRUE(HLIB_MICROSOFT_COMPILER)
	#define HLIB_IS_POD(x) (!__is_class(x) || __is_pod(x))
#else
	#define HLIB_IS_POD(x) false
#endif

HLIB_BEGIN()

template<class T, bool pod = HLIB_IS_POD(T)>
struct pod_traits {};

template<class T>
struct remove_reference { using type = T; };

template<class T>
struct remove_reference<T&> { using type = T; };

template<class T>
struct remove_reference<T&&> { using type = T; };

template<class T, T t> struct swappable;

template<typename T>
static inline void move(T& a, T& b);

template<typename T>
static inline void move_construct(T* a, T& b);

#include <details/traits.inl>

HLIB_END()
