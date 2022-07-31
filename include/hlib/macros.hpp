/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <platform.hpp>

// Is this a debug build??
#if defined(_DEBUG)
	#define HLIB_DEBUG 1
#else 
	#define HLIB_DEBUG 0
#endif

// Are you exporting or importing hlib??
#if defined(_DLL)
	#define HLIB_STATIC_EXPORT 1
#else
	#define HLIB_STATIC_EXPORT 0
#endif

// Helper macro
#define MACRO_TRUE(def) (def == 1)
#define MACRO_FALSE(def) !MACRO_TRUE(def)

// Make hlib functionality migrate to your project (^w^)
#if MACRO_TRUE(HLIB_STATIC_EXPORT) &&  MACRO_TRUE(HLIB_MICROSOFT_COMPILER)
	#define _HLIB __declspec(dllexport)
#else
	#define _HLIB __declspec(dllimport)
#endif

// Some compiler-specific predefined integer types and more
#if MACRO_TRUE(HLIB_MICROSOFT_COMPILER)
	#define HLIB_STATIC_TYPE_8BIT  __int8
	#define HLIB_STATIC_TYPE_16BIT __int16
	#define HLIB_STATIC_TYPE_32BIT __int32
	#define HLIB_STATIC_TYPE_64BIT __int64

	#define HLIB_NOEXCEPT noexcept
	#define HLIB_THROW() throw()
	#define HLIB_DEBUGBREAK() __debugbreak()

	#define HLIB_WIDE_CHAR_TYPE wchar_t	
#else
	#define HLIB_STATIC_TYPE_8BIT  char
	#define HLIB_STATIC_TYPE_16BIT short
	#define HLIB_STATIC_TYPE_32BIT int
	#define HLIB_STATIC_TYPE_64BIT long long

	#define HLIB_NOEXCEPT 
	#define HLIB_THROW() throw()
	#define HLIB_DEBUGBREAK() 

	#define HLIB_WIDE_CHAR_TYPE unsigned short
#endif

// ...and more predefined useful types
#if MACRO_TRUE(HLIB_64BIT_BUILD)
	#define HLIB_SIZE_TYPE    long long unsigned int
	#define HLIB_PTRDIFF_TYPE					 HLIB_STATIC_TYPE_64BIT
	#define HLIB_INTPTR_TYPE					 HLIB_STATIC_TYPE_64BIT
#else
	#define HLIB_SIZE_TYPE    unsigned           HLIB_STATIC_TYPE_32BIT
	#define HLIB_PTRDIFF_TYPE                    HLIB_STATIC_TYPE_32BIT
	#define HLIB_INTPTR_TYPE					 HLIB_STATIC_TYPE_32BIT
#endif

#if MACRO_FALSE(__BOOL_DEFINED)
	#define bool HLIB_STATIC_TYPE_8BIT
	#define true  (bool)1
	#define false (bool)0
#endif

/* 
 - No, that's not a mistake. XD
 - This is actually nullptr_t
 - But Bullptr..
 - It's can be funny? Really?
 - *really sad sounds*
*/
#define HLIB_BULLPTR_TYPE decltype(nullptr)

// Helper macros
#define HLIB_TEMPLATE1(class_name) template<class class_name>
#define HLIB_TEMPLATE2(class_name, class_name2) template<class class_name, class class_name2>
#define HLIB_TEMPLATE3(class_name, class_name2, class_name3) template<class class_name, class class_name2, class class_name3>

#define HLIB_PUSH_WARNING() __pragma(warning(push))
#define HLIB_DISABLE_WARNING(number) __pragma(warning(disable: number))
#define HLIB_POP_WARNING() __pragma(warning(pop))
#define HLIB_POP_WARNINGS() HLIB_POP_WARNING()

#define HLIB_DISABLE_ALL_WARNINGS() \
HLIB_PUSH_WARNING() \
HLIB_DISABLE_WARNING(26451) \
HLIB_DISABLE_WARNING(4311) \
HLIB_DISABLE_WARNING(4302)

// Helper macros to make easier namespace changing maybe..
#define HLIB_BEGIN() HLIB_DISABLE_ALL_WARNINGS() namespace hlib {
#define HLIB_END() } HLIB_POP_WARNINGS()
