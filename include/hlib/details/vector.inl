template<class T, class Alloc>
inline vector<T, Alloc>::vector() {
	_Buff_Structure__init(&m_buffer);
}

template<class T, class Alloc>
inline vector<T, Alloc>::vector(const vector& other) {
	_Buff_Structure__init(&m_buffer);
	_Buff_Structure__reserve(&m_buffer, other.size());
	_Buff_Structure__insert(&m_buffer, m_buffer.last, other.m_buffer.first, other.m_buffer.last);
}

template<class T, class Alloc>
inline vector<T, Alloc>::vector(vector&& other) {
	_Buff_Structure__move(&m_buffer, &other.m_buffer);
}

template<class T, class Alloc>
inline vector<T, Alloc>::vector(size_t size) {
	_Buff_Structure__init(&m_buffer);
	_Buff_Structure__resize(&m_buffer, size);
}

template<class T, class Alloc>
inline vector<T, Alloc>::vector(size_t size, const T& value) {
	_Buff_Structure__init(&m_buffer);
	_Buff_Structure__resize(&m_buffer, size, value);
}

template<class T, class Alloc>
inline vector<T, Alloc>::vector(const T* first, const T* last) {
	_Buff_Structure__init(&m_buffer);
	_Buff_Structure__insert(&m_buffer, m_buffer.last, first, last);
}

template<class T, class Alloc>
inline vector<T, Alloc>::~vector() {
	_Buff_Structure__destroy(&m_buffer);
}

template<class T, class Alloc>
inline vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& other) {
	vector(other).swap(*this);
	return *this;
}

template<class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& other) {
	_Buff_Structure__destroy(&m_buffer);
	_Buff_Structure__move(&m_buffer, &other.m_buffer);
	return *this;
}

template<class T, class Alloc>
inline void vector<T, Alloc>::assign(const T* first, const T* last) {
	_Buff_Structure__clear(&m_buffer);
	_Buff_Structure__insert(&m_buffer, m_buffer.last, first, last);
}

template<class T, class Alloc>
inline const T* vector<T, Alloc>::data() const {
	return m_buffer.first;
}

template<class T, class Alloc>
inline T* vector<T, Alloc>::data() {
	return m_buffer.first;
}

template<class T, class Alloc>
inline size_t vector<T, Alloc>::size() const {
	return (size_t)(m_buffer.last - m_buffer.first);
}

template<class T, class Alloc>
inline size_t vector<T, Alloc>::capacity() const {
	return (size_t)(m_buffer.capacity - m_buffer.first);
}

template<class T, class Alloc>
inline bool vector<T, Alloc>::empty() const {
	return m_buffer.last == m_buffer.first;
}

template<class T, class Alloc>
inline T& vector<T, Alloc>::operator[](size_t idx) {
	return m_buffer.first[idx];
}

template<class T, class Alloc>
inline const T& vector<T, Alloc>::operator[](size_t idx) const {
	return m_buffer.first[idx];
}

template<class T, class Alloc>
inline const T& vector<T, Alloc>::front() const {
	return m_buffer.first[0];
}

template<class T, class Alloc>
inline T& vector<T, Alloc>::front() {
	return m_buffer.first[0];
}

template<class T, class Alloc>
inline const T& vector<T, Alloc>::back() const {
	return m_buffer.last[-1];
}

template<class T, class Alloc>
inline T& vector<T, Alloc>::back() {
	return m_buffer.last[-1];
}

template<class T, class Alloc>
inline void vector<T, Alloc>::resize(size_t size) {
	_Buff_Structure__resize(&m_buffer, size);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::resize(size_t size, const T& value) {
	_Buff_Structure__resize(&m_buffer, size, value);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::clear() {
	_Buff_Structure__clear(&m_buffer);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::reserve(size_t capacity) {
	_Buff_Structure__reserve(&m_buffer, capacity);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::push_back(const T& t) {
	_Buff_Structure__append(&m_buffer, &t);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::emplace_back() {
	_Buff_Structure__append(&m_buffer);
}

template<class T, class Alloc>
template<class Param>
inline void vector<T, Alloc>::emplace_back(const Param& param) {
	_Buff_Structure__append(&m_buffer, &param);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::pop_back() {
	_Buff_Structure__erase(&m_buffer, m_buffer.last - 1, m_buffer.last);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::shrink_to_fit() {
	_Buff_Structure__shrink_to_fit(&m_buffer);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::swap(vector& other) {
	_Buff_Structure__swap(&m_buffer, &other.m_buffer);
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
	return m_buffer.first;
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
	return m_buffer.last;
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
	return m_buffer.first;
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
	return m_buffer.last;
}

template<class T, class Alloc>
inline void vector<T, Alloc>::insert(typename vector::iterator where) {
	_Buff_Structure__insert(&m_buffer, where, 1);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::insert(iterator where, const T& value) {
	_Buff_Structure__insert(&m_buffer, where, &value, &value + 1);
}

template<class T, class Alloc>
inline void vector<T, Alloc>::insert(iterator where, const T* first, const T* last) {
	_Buff_Structure__insert(&m_buffer, where, first, last);
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator where) {
	return _Buff_Structure__erase(&m_buffer, where, where + 1);
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) {
	return _Buff_Structure__erase(&m_buffer, first, last);
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unordered(iterator where) {
	return _Buff_Structure__erase_unordered(&m_buffer, where, where + 1);
}

template<class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase_unordered(iterator first, iterator last) {
	return _Buff_Structure__erase_unordered(&m_buffer, first, last);
}

template<class T, class Alloc>
template<class Param>
void vector<T, Alloc>::emplace(typename vector::iterator where, const Param& param) {
	_Buff_Structure__insert(&m_buffer, where, &param, &param + 1);
}