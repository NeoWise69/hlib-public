template<class T>
inline size_t hash(const T& value) {
	const size_t asint = (size_t)value;
	return strhash((const char*)&asint, sizeof(asint));
}