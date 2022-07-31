template<class T>
static inline void _Buff_Structure__destroy_range_traits(T* first, T* last, pod_traits<T, false>);

template<class T>
static inline void _Buff_Structure__destroy_range_traits(T*, T*, pod_traits<T, true>) {}

template<class T>
static inline void _Buff_Structure__destroy_range(T* first, T* last);

template<class T>
static inline void _Buff_Structure__fill_urange_traits(T* first, T* last, pod_traits<T, false>);

template<class T>
static inline void _Buff_Structure__fill_urange_traits(T* first, T* last, pod_traits<T, true>);

template<class T>
static inline void _Buff_Structure__fill_urange_traits(T* first, T* last, const T& value, pod_traits<T, false>);

template<class T>
static inline void _Buff_Structure__fill_urange_traits(T* first, T* last, const T& value, pod_traits<T, true>);

template<class T>
static inline void _Buff_Structure__move_urange_traits(T* dest, T* first, T* last, pod_traits<T, false>);

template<class T>
static inline void _Buff_Structure__move_urange_traits(T* dest, T* first, T* last, pod_traits<T, true>);

template<class T>
static inline void _Buff_Structure__bmove_urange_traits(T* dest, T* first, T* last, pod_traits<T, false>);

template<class T>
static inline void _Buff_Structure__bmove_urange_traits(T* dest, T* first, T* last, pod_traits<T, true>);

template<class T>
static inline void _Buff_Structure__move_urange(T* dest, T* first, T* last);

template<class T>
static inline void _Buff_Structure__bmove_urange(T* dest, T* first, T* last);

template<class T>
static inline void _Buff_Structure__fill_urange(T* first, T* last);

template<class T>
static inline void _Buff_Structure__fill_urange(T* first, T* last, const T& value);

template<class T>
inline void _Buff_Structure__destroy_range_traits(T* first, T* last, pod_traits<T, false>) {
	for (; first < last; ++first)
		first->~T();
}

template<class T>
inline void _Buff_Structure__destroy_range(T* first, T* last) {
	_Buff_Structure__destroy_range_traits(first, last, pod_traits<T>());
}

template<class T>
inline void _Buff_Structure__fill_urange_traits(T* first, T* last, pod_traits<T, false>) {
	for (; first < last; ++first)
		new(placeholder(), first) T();
}

template<class T>
inline void _Buff_Structure__fill_urange_traits(T* first, T* last, pod_traits<T, true>) {
	for (; first < last; ++first)
		*first = T();
}

template<class T>
inline void _Buff_Structure__fill_urange_traits(T* first, T* last, const T& value, pod_traits<T, false>) {
	for (; first < last; ++first)
		new(placeholder(), first) T(value);
}

template<class T>
inline void _Buff_Structure__fill_urange_traits(T* first, T* last, const T& value, pod_traits<T, true>) {
	for (; first < last; ++first)
		*first = value;
}

template<class T>
inline void _Buff_Structure__move_urange_traits(T* dest, T* first, T* last, pod_traits<T, false>) {
	for (T* it = first; it != last; ++it, ++dest)
		move_construct(dest, *it);
	_Buff_Structure__destroy_range(first, last);
}

template<class T>
inline void _Buff_Structure__move_urange_traits(T* dest, T* first, T* last, pod_traits<T, true>) {
	for (; first != last; ++first, ++dest)
		*dest = *first;
}

template<class T>
inline void _Buff_Structure__bmove_urange_traits(T* dest, T* first, T* last, pod_traits<T, false>) {
	dest += (last - first);
	for (T* it = last; it != first; --it, --dest) {
		move_construct(dest - 1, *(it - 1));
		_Buff_Structure__destroy_range(it - 1, it);
	}
}

template<class T>
inline void _Buff_Structure__bmove_urange_traits(T* dest, T* first, T* last, pod_traits<T, true>) {
	dest += (last - first);
	for (T* it = last; it != first; --it, --dest)
		*(dest - 1) = *(it - 1);
}

template<class T>
inline void _Buff_Structure__move_urange(T* dest, T* first, T* last) {
	_Buff_Structure__move_urange_traits(dest, first, last, pod_traits<T>());
}

template<class T>
inline void _Buff_Structure__bmove_urange(T* dest, T* first, T* last) {
	_Buff_Structure__bmove_urange_traits(dest, first, last, pod_traits<T>());
}

template<class T>
inline void _Buff_Structure__fill_urange(T* first, T* last) {
	_Buff_Structure__fill_urange_traits(first, last, pod_traits<T>());
}

template<class T>
inline void _Buff_Structure__fill_urange(T* first, T* last, const T& value) {
	_Buff_Structure__fill_urange_traits(first, last, value, pod_traits<T>());
}

template<class T, class Alloc>
inline void _Buff_Structure__init(_Buf_Structure_<T, Alloc>* b) {
	b->first = b->last = b->capacity = 0;
}

template<class T, class Alloc>
inline void _Buff_Structure__destroy(_Buf_Structure_<T, Alloc>* b) {
	_Buff_Structure__destroy_range(b->first, b->last);
	Alloc::deallocate(b->first, (size_t)((char*)b->capacity - (char*)b->first));
}

template<class T, class Alloc>
inline void _Buff_Structure__reserve(_Buf_Structure_<T, Alloc>* b, size_t capacity) {
	if (b->first + capacity <= b->capacity)
		return;

	typedef T* pointer;
	const size_t size = (size_t)(b->last - b->first);
	pointer newfirst = (pointer)Alloc::allocate(sizeof(T) * capacity);
	_Buff_Structure__move_urange(newfirst, b->first, b->last);
	Alloc::deallocate(b->first, sizeof(T) * capacity);

	b->first = newfirst;
	b->last = newfirst + size;
	b->capacity = newfirst + capacity;
}

template<class T, class Alloc>
inline void _Buff_Structure__resize(_Buf_Structure_<T, Alloc>* b, size_t size) {
	_Buff_Structure__reserve(b, size);

	_Buff_Structure__fill_urange(b->last, b->first + size);
	_Buff_Structure__destroy_range(b->first + size, b->last);
	b->last = b->first + size;
}

template<class T, class Alloc>
inline void _Buff_Structure__resize(_Buf_Structure_<T, Alloc>* b, size_t size, const T& value) {
	_Buff_Structure__reserve(b, size);

	_Buff_Structure__fill_urange(b->last, b->first + size, value);
	_Buff_Structure__destroy_range(b->first + size, b->last);
	b->last = b->first + size;
}

template<class T, class Alloc>
inline void _Buff_Structure__shrink_to_fit(_Buf_Structure_<T, Alloc>* b) {
	if (b->capacity != b->last) {
		if (b->last == b->first) {
			const size_t capacity = (size_t)(b->capacity - b->first);
			Alloc::deallocate(b->first, sizeof(T) * capacity);
			b->capacity = b->first = b->last = nullptr;
		}
		else {
			const size_t capacity = (size_t)(b->capacity - b->first);
			const size_t size = (size_t)(b->last - b->first);
			T* newfirst = (T*)Alloc::allocate(sizeof(T) * size);
			_Buff_Structure__move_urange(newfirst, b->first, b->last);
			Alloc::deallocate(b->first, sizeof(T) * capacity);
			b->first = newfirst;
			b->last = newfirst + size;
			b->capacity = b->last;
		}
	}
}

template<class T, class Alloc>
inline void _Buff_Structure__clear(_Buf_Structure_<T, Alloc>* b) {
	_Buff_Structure__destroy_range(b->first, b->last);
	b->last = b->first;
}

template<class T, class Alloc>
inline T* _Buff_Structure__insert_common(_Buf_Structure_<T, Alloc>* b, T* where, size_t count) {
	const size_t offset = (size_t)(where - b->first);
	const size_t newsize = (size_t)((b->last - b->first) + count);
	if (b->first + newsize > b->capacity)
		_Buff_Structure__reserve(b, (newsize * 3) / 2);

	where = b->first + offset;

	if (where != b->last)
		_Buff_Structure__bmove_urange(where + count, where, b->last);

	b->last = b->first + newsize;

	return where;
}

template<class T, class Alloc, class Param>
inline void _Buff_Structure__insert(_Buf_Structure_<T, Alloc>* b, T* where, const Param* first, const Param* last) {
	typedef const char* pointer;
	const size_t count = last - first;
	const bool frombuf = ((pointer)b->first <= (pointer)first && (pointer)b->last >= (pointer)last);
	size_t offset;
	if (frombuf) {
		offset = (pointer)first - (pointer)b->first;
		if ((pointer)where <= (pointer)first)
			offset += count * sizeof(T);
		where = _Buff_Structure__insert_common(b, where, count);
		first = (Param*)((pointer)b->first + offset);
		last = first + count;
	}
	else {
		where = _Buff_Structure__insert_common(b, where, count);
	}
	for (; first != last; ++first, ++where)
		new(placeholder(), where) T(*first);
}

template<class T, class Alloc>
inline void _Buff_Structure__insert(_Buf_Structure_<T, Alloc>* b, T* where, size_t count) {
	where = _Buff_Structure__insert_common(b, where, count);
	for (T* end = where + count; where != end; ++where)
		new(placeholder(), where) T();
}

template<class T, class Alloc, class Param>
inline void _Buff_Structure__append(_Buf_Structure_<T, Alloc>* b, const Param* param) {
	if (b->capacity != b->last) {
		new(placeholder(), b->last) T(*param);
		++b->last;
	}
	else {
		_Buff_Structure__insert(b, b->last, param, param + 1);
	}
}

template<class T, class Alloc>
inline void _Buff_Structure__append(_Buf_Structure_<T, Alloc>* b) {
	if (b->capacity != b->last) {
		new(placeholder(), b->last) T();
		++b->last;
	}
	else {
		_Buff_Structure__insert(b, b->last, 1);
	}
}

template<class T, class Alloc>
inline T* _Buff_Structure__erase(_Buf_Structure_<T, Alloc>* b, T* first, T* last) {
	typedef T* pointer;
	const size_t count = (last - first);
	for (pointer it = last, end = b->last, dest = first; it != end; ++it, ++dest)
		move(*dest, *it);

	_Buff_Structure__destroy_range(b->last - count, b->last);

	b->last -= count;
	return first;
}

template<class T, class Alloc>
inline T* _Buff_Structure__erase_unordered(_Buf_Structure_<T, Alloc>* b, T* first, T* last) {
	typedef T* pointer;
	const size_t count = (last - first);
	const size_t tail = (b->last - last);
	pointer it = b->last - ((count < tail) ? count : tail);
	for (pointer end = b->last, dest = first; it != end; ++it, ++dest)
		move(*dest, *it);

	_Buff_Structure__destroy_range(b->last - count, b->last);

	b->last -= count;
	return first;
}

template<class T, class Alloc>
inline void _Buff_Structure__swap(_Buf_Structure_<T, Alloc>* b, _Buf_Structure_<T, Alloc>* other) {
	typedef T* pointer;
	const pointer tfirst = b->first, tlast = b->last, tcapacity = b->capacity;
	b->first = other->first, b->last = other->last, b->capacity = other->capacity;
	other->first = tfirst, other->last = tlast, other->capacity = tcapacity;
}

template<class T, class Alloc>
inline void _Buff_Structure__move(_Buf_Structure_<T, Alloc>* dst, _Buf_Structure_<T, Alloc>* src) {
	dst->first = src->first, dst->last = src->last, dst->capacity = src->capacity;
	src->first = src->last = src->capacity = nullptr;
}
