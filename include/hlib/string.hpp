/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <static_allocator.hpp>
#include <hash.hpp>

HLIB_BEGIN()

template<class Char, class Alloc>
class _HLIB basic_string {
public:
	basic_string();
	basic_string(const basic_string& other);
	basic_string(basic_string&& other);
	basic_string(const Char* sz);
	basic_string(const Char* sz, size_t len);
	~basic_string();
public:
	basic_string& operator=(const basic_string& other);
	basic_string& operator=(basic_string&& other);
public:
	const Char* c_str() const;
	size_t size() const;
	void reserve(size_t capacity);
	void resize(size_t size);
	void clear();
	void append(const Char* first, const Char* last);
	void assign(const Char* s, size_t n);
	void shrink_to_fit();
	void swap(basic_string& other);
private:
	typedef Char* ptr;
	ptr m_first;
	ptr m_last;
	ptr m_capacity;

	static const size_t c_nbuffer = 12;
	Char m_buffer[12];
};

template<class Char, class LAlloc, class RAlloc>
static inline bool operator==(const basic_string<Char, LAlloc>& lhs, const basic_string<Char, RAlloc>& rhs);

template<class Char, class Alloc>
static inline size_t hash(const basic_string<Char, Alloc>& value);

_HLIB size_t strlen(const char* str);
_HLIB i32 strcmp(const char* str1, const char* str2);

using string  = basic_string<char, HLIB_STATIC_ALLOCATOR>;

#include <details/string.inl>

HLIB_END()
