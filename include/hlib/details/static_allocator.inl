
inline void* static_allocator::allocate(size_t bytes) HLIB_NOEXCEPT {
	return malloc(bytes);
}

inline void  static_allocator::deallocate(void* ptr, size_t /*bytes*/) HLIB_NOEXCEPT {
	free(ptr);
}
