/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <static_allocator.hpp>
#include <new.hpp>
#include <traits.hpp>

HLIB_BEGIN()

// interface buffer structure
template<class T, class Alloc = HLIB_STATIC_ALLOCATOR>
struct _HLIB _Buf_Structure_ {
	T* first;
	T* last;
	T* capacity;
};

template<class T, class Alloc>
static inline void _Buff_Structure__init(_Buf_Structure_<T, Alloc>* b);

template<class T, class Alloc>
static inline void _Buff_Structure__destroy(_Buf_Structure_<T, Alloc>* b);

template<class T, class Alloc>
static inline void _Buff_Structure__reserve(_Buf_Structure_<T, Alloc>* b, size_t capacity);

template<class T, class Alloc>
static inline void _Buff_Structure__resize(_Buf_Structure_<T, Alloc>* b, size_t size);

template<class T, class Alloc>
static inline void _Buff_Structure__resize(_Buf_Structure_<T, Alloc>* b, size_t size, const T& value);

template<class T, class Alloc>
static inline void _Buff_Structure__shrink_to_fit(_Buf_Structure_<T, Alloc>* b);

template<class T, class Alloc>
static inline void _Buff_Structure__clear(_Buf_Structure_<T, Alloc>* b);

template<class T, class Alloc>
static inline T* _Buff_Structure__insert_common(_Buf_Structure_<T, Alloc>* b, T* where, size_t count);

template<class T, class Alloc, class Param>
static inline void _Buff_Structure__insert(_Buf_Structure_<T, Alloc>* b, T* where, const Param* first, const Param* last);

template<class T, class Alloc>
static inline void _Buff_Structure__insert(_Buf_Structure_<T, Alloc>* b, T* where, size_t count);

template<class T, class Alloc, class Param>
static inline void _Buff_Structure__append(_Buf_Structure_<T, Alloc>* b, const Param* param);

template<class T, class Alloc>
static inline void _Buff_Structure__append(_Buf_Structure_<T, Alloc>* b);

template<class T, class Alloc>
static inline T* _Buff_Structure__erase(_Buf_Structure_<T, Alloc>* b, T* first, T* last);

template<class T, class Alloc>
static inline T* _Buff_Structure__erase_unordered(_Buf_Structure_<T, Alloc>* b, T* first, T* last);

template<class T, class Alloc>
static inline void _Buff_Structure__swap(_Buf_Structure_<T, Alloc>* b, _Buf_Structure_<T, Alloc>* other);

template<class T, class Alloc>
static inline void _Buff_Structure__move(_Buf_Structure_<T, Alloc>* dst, _Buf_Structure_<T, Alloc>* src);

#include <details/buffer.inl>

HLIB_END()
