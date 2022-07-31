#include "..\string.hpp"
template<class Char, class Alloc>
basic_string<Char, Alloc>::basic_string()
	: m_first(m_buffer)
	, m_last(m_buffer)
	, m_capacity(m_buffer + c_nbuffer)
{
	resize(0);
}

template<class Char, class Alloc>
basic_string<Char, Alloc>::basic_string(const basic_string& other)
	: m_first(m_buffer)
	, m_last(m_buffer)
	, m_capacity(m_buffer + c_nbuffer)
{
	reserve(other.size());
	append(other.m_first, other.m_last);
}

template<class Char, class Alloc>
basic_string<Char, Alloc>::basic_string(basic_string&& other)
{
	if (other.m_first == other.m_buffer) {
		m_first = m_buffer;
		m_last = m_buffer;
		m_capacity = m_buffer + c_nbuffer;
		reserve(other.size());
		append(other.m_first, other.m_last);
	}
	else {
		m_first = other.m_first;
		m_last = other.m_last;
		m_capacity = other.m_capacity;
	}
	other.m_first = other.m_last = other.m_buffer;
	other.m_capacity = other.m_buffer + c_nbuffer;
	other.resize(0);
}

template<class Char, class Alloc>
basic_string<Char, Alloc>::basic_string(const Char* sz)
	: m_first(m_buffer)
	, m_last(m_buffer)
	, m_capacity(m_buffer + c_nbuffer)
{
	size_t len = 0;
	for (const Char* it = sz; *it; ++it)
		++len;

	reserve(len);
	append(sz, sz + len);

	m_first[++len] = 0;
}

template<class Char, class Alloc>
basic_string<Char, Alloc>::basic_string(const Char* sz, size_t len)
	: m_first(m_buffer)
	, m_last(m_buffer)
	, m_capacity(m_buffer + c_nbuffer)
{
	reserve(len);
	append(sz, sz + len);
}

template<class Char, class Alloc>
basic_string<Char, Alloc>::~basic_string()
{
	if (m_first != m_buffer)
		Alloc::deallocate(m_first, m_capacity - m_first);
}

template<class Char, class Alloc>
basic_string<Char, Alloc>& basic_string<Char, Alloc>::operator=(const basic_string& other) {
	basic_string(other).swap(*this);
	return *this;
}

template<class Char, class Alloc>
basic_string<Char, Alloc>& basic_string<Char, Alloc>::operator=(basic_string&& other) {
	basic_string(static_cast<basic_string&&>(other)).swap(*this);
	return *this;
}

template<class Char, class Alloc>
const Char* basic_string<Char, Alloc>::c_str() const {
	return m_first;
}

template<class Char, class Alloc>
size_t basic_string<Char, Alloc>::size() const
{
	return (size_t)(m_last - m_first);
}

template<class Char, class Alloc>
void basic_string<Char, Alloc>::reserve(size_t capacity)
{
	constexpr unsigned typesize = sizeof(Char);

	if (m_first + capacity + typesize <= m_capacity)
		return;

	const size_t size = (size_t)(m_last - m_first);

	ptr newfirst = (ptr)Alloc::allocate(capacity + typesize);
	for (ptr it = m_first, newit = newfirst, end = m_last; it != end; ++it, ++newit)
		*newit = *it;
	if (m_first != m_buffer)
		Alloc::deallocate(m_first, m_capacity - m_first);

	m_first = newfirst;
	m_last = newfirst + size;
	m_capacity = m_first + capacity;
}

template<class Char, class Alloc>
void basic_string<Char, Alloc>::resize(size_t size)
{
	const size_t prevSize = m_last - m_first;
	reserve(size);
	if (size > prevSize)
		for (ptr it = m_last, end = m_first + size + 1; it < end; ++it)
			*it = 0;
	else if (m_last != m_first)
		m_first[size] = 0;

	m_last = m_first + size;
}

template<class Char, class Alloc>
void basic_string<Char, Alloc>::clear() {
	resize(0);
}

template<class Char, class Alloc>
void basic_string<Char, Alloc>::append(const Char* first, const Char* last)
{
	const size_t newsize = (size_t)((m_last - m_first) + (last - first) + sizeof(Char));
	if (m_first + newsize > m_capacity)
		reserve((newsize * 3) / 2);

	for (; first != last; ++m_last, ++first)
		*m_last = *first;
	*m_last = 0;
}

template<class Char, class Alloc>
void basic_string<Char, Alloc>::assign(const Char* s, size_t n)
{
	clear();
	append(s, s + n);
}

template<class Char, class Alloc>
void basic_string<Char, Alloc>::shrink_to_fit() {
	if (m_first == m_buffer) {
	}
	else if (m_last == m_first) {
		const size_t capacity = (size_t)(m_capacity - m_first);
		if (capacity)
			Alloc::deallocate(m_first, capacity + 1);
		m_capacity = m_first;
	}
	else if (m_capacity != m_last) {
		const size_t size = (size_t)(m_last - m_first);
		Char* newfirst = (ptr)Alloc::allocate(size + 1);
		for (ptr in = m_first, out = newfirst; in != m_last + 1; ++in, ++out)
			*out = *in;
		if (m_first != m_capacity)
			Alloc::deallocate(m_first, m_capacity + 1 - m_first);
		m_first = newfirst;
		m_last = newfirst + size;
		m_capacity = m_last;
	}
}

template<class Char, class Alloc>
void basic_string<Char, Alloc>::swap(basic_string& other) {
	const ptr tfirst = m_first, tlast = m_last, tcapacity = m_capacity;
	m_first = other.m_first, m_last = other.m_last, m_capacity = other.m_capacity;
	other.m_first = tfirst, other.m_last = tlast, other.m_capacity = tcapacity;

	Char tbuffer[c_nbuffer];

	if (m_first == other.m_buffer)
		for (ptr it = other.m_buffer, end = m_last, out = tbuffer; it != end; ++it, ++out)
			*out = *it;

	if (other.m_first == m_buffer) {
		other.m_last = other.m_last - other.m_first + other.m_buffer;
		other.m_first = other.m_buffer;
		other.m_capacity = other.m_buffer + c_nbuffer;

		for (ptr it = other.m_first, end = other.m_last, in = m_buffer; it != end; ++it, ++in)
			*it = *in;
		*other.m_last = 0;
	}

	if (m_first == other.m_buffer) {
		m_last = m_last - m_first + m_buffer;
		m_first = m_buffer;
		m_capacity = m_buffer + c_nbuffer;

		for (ptr it = m_first, end = m_last, in = tbuffer; it != end; ++it, ++in)
			*it = *in;
		*m_last = 0;
	}
}

template<class Char, class LAlloc, class RAlloc>
inline bool operator==(const basic_string<Char, LAlloc>& lhs, const basic_string<Char, RAlloc>& rhs) {
	typedef const Char* ptr;

	const size_t lsize = lhs.size(), rsize = rhs.size();
	if (lsize != rsize)
		return false;

	ptr lit = lhs.c_str(), rit = rhs.c_str();
	ptr lend = lit + lsize;
	while (lit != lend)
		if (*lit++ != *rit++)
			return false;

	return true;
}

template<class Char, class Alloc>
inline size_t hash(const basic_string<Char, Alloc>& value) {
	return hash_string(value.c_str(), value.size());
}
