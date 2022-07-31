/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <traits.hpp>
#include <int.hpp>

HLIB_BEGIN()

/*
 A class template that provides a way to store two heterogeneous objects as a single unit. 
 * If neither T1 nor T2 is a possibly cv-qualified class type with non-trivial destructor, 
 * or array thereof, the destructor of pair is trivial.
*/
template<class F, class S>
struct pair {
	pair() HLIB_NOEXCEPT;
	pair(const pair& other) HLIB_NOEXCEPT;
	pair(pair&& other) HLIB_NOEXCEPT;
	pair(const F& key, const S& value) HLIB_NOEXCEPT;
	pair(F&& key, S&& value) HLIB_NOEXCEPT;

	pair& operator=(const pair& other);
	pair& operator=(pair&& other);

	F first;
	S second;
};

// Creates a pair object of type, defined by the argument types
template<class F, class S>
static inline pair<typename remove_reference<F>::type, typename remove_reference<S>::type>
make_pair(F&& f, S&& s);

#include <details/pair.inl>

HLIB_END()
