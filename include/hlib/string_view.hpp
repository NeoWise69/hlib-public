/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <int.hpp>

HLIB_BEGIN()

class
_HLIB
string_view {
public:
	typedef char value_type;
	typedef char* pointer;
	typedef const char* const_pointer;
	typedef char& reference;
	typedef const char& const_reference;
	typedef const_pointer iterator;
	typedef const_pointer const_iterator;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	static constexpr size_type npos = size_type(-1);
public:
	constexpr string_view();
	constexpr string_view(const char* s, size_type count);
	constexpr string_view(const char* s);
	constexpr string_view(const string_view&) = default;
	string_view& operator=(const string_view&) = default;
public:
	constexpr const char* data() const;
	constexpr char operator[](size_type pos) const;
	constexpr size_type size() const;
	constexpr bool empty() const;
	constexpr iterator begin() const;
	constexpr const_iterator cbegin() const;
	constexpr iterator end() const;
	constexpr const_iterator cend() const;
	constexpr string_view substr(size_type pos = 0, size_type count = npos) const;
	constexpr void swap(string_view& v);
private:
	string_view(decltype(nullptr)) = delete;
	static constexpr size_type strlen(const char* s);
private:
	const char* m_str;
	size_type m_size;
};

HLIB_END()
