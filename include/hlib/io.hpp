/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>
#include <int.hpp>

HLIB_BEGIN()

// Basic file structure that handles by Operating System
typedef struct FILE__ {
	void* pPlaceholder;
	// File size in bytes
	size_t fSize;
} FILE, *FILEPTR;

#define FILE_INVALID (FILE*)-1

namespace omode {
	enum : u32 { 
		// open file only for reading
		read = 1,
		// open file for writing (reading supported)
		write
};}
/*
	Open file intarface for work with
	ALWAYS CLOSE FILE HANDLES!
*/
_HLIB FILE* 
fopen(const char* filename, u32 openmode = omode::read);

/*
	Close file intarface.
	ALWAYS CLOSE FILE HANDLES!
*/
_HLIB bool 
fclose(FILE* f);

/*
	Writes file content to output buffer(char array, or pointer to char array)
*/
_HLIB bool 
fread(FILE* f, i8* outbuff);

/*
	@returns File content(char array, or pointer to char array)
*/
_HLIB i8* 
fread(FILE* f);

/*
	Writes content to file with given size of data
*/
_HLIB bool 
fwrite(FILE* f, i8* data, size_t len);

/*
	Prints formatted string to debug output (VisualStudio thing)
*/
_HLIB void
dprintf(const char* msg);

/*
	Man, it's just regular printf function...
*/
_HLIB void
printf(const char* format, ...);

HLIB_END()
