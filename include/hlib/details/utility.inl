template<class T>
inline T&& forward(typename remove_reference<T>::type& parameter) HLIB_NOEXCEPT {
	return static_cast<T&&>(parameter);
}