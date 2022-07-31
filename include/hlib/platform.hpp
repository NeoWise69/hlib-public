/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once

// Detect, if we have a Microsoft's Compiler (MSVC)
#if defined(_MSC_VER)
	#define HLIB_MICROSOFT_COMPILER 1
#else
	#define HLIB_MICROSOFT_COMPILER 0
#endif

// Detect, if we are on the Windows-based Operating System
#if defined(_WIN32) || defined(WIN32)
	#define HLIB_WIN32 1
#else
	#define HLIB_WIN32 0
#endif

// Detect, if we are on the 64-bit Machine
#if defined(_M_X64)
#define HLIB_64BIT_BUILD 1
#else
#define HLIB_64BIT_BUILD 0
#endif
