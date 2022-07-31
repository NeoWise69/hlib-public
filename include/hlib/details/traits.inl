template<class T>
static inline void move_impl(T& a, T& b, ...) {
	a = b;
}

template<class T>
static inline void move_impl(T& a, T& b, T*, swappable<void (T::*)(T&), &T::swap>* = 0) {
	a.swap(b);
}

template<class T>
inline void move(T& a, T& b) {
	move_impl(a, b, (T*)0);
}

template<class T>
static inline void move_construct_impl(T* a, T& b, ...) {
	new(placeholder(), a) T(b);
}

template<class T>
static inline void move_construct_impl(T* a, T& b, void*, swappable<void (T::*)(T&), &T::swap>* = 0) {
	// If your type T does not have a default constructor, simply insert:
	// struct tinystl_nomove_construct;
	// in the class definition
	new(placeholder(), a) T;
	a->swap(b);
}

template<class T>
static inline void move_construct_impl(T* a, T& b, T*, class T::tinystl_nomove_construct* = 0) {
	new(placeholder(), a) T(b);
}

template<class T>
inline void move_construct(T* a, T& b) {
	move_construct_impl(a, b, (T*)0);
}
