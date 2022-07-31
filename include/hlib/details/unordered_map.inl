template<class Key, class Value, class Alloc>
inline unordered_map<Key, Value, Alloc>::unordered_map()
	: m_size(0)
{
	_Buff_Structure__init<pointer, Alloc>(&m_buckets);
	_Buff_Structure__resize<pointer, Alloc>(&m_buckets, 9, 0);
}

template<class Key, class Value, class Alloc>
inline unordered_map<Key, Value, Alloc>::unordered_map(const unordered_map& other)
	: m_size(other.m_size)
{
	const size_t nbuckets = (size_t)(other.m_buckets.last - other.m_buckets.first);
	_Buff_Structure__init<pointer, Alloc>(&m_buckets);
	_Buff_Structure__resize<pointer, Alloc>(&m_buckets, nbuckets, 0);

	for (pointer it = *other.m_buckets.first; it; it = it->next) {
		unordered_hash_node<Key, Value>* newnode = new(placeholder(), Alloc::allocate(sizeof(unordered_hash_node<Key, Value>))) unordered_hash_node<Key, Value>(it->first, it->second);
		newnode->next = newnode->prev = 0;

		unordered_hash_node_insert(newnode, hash(it->first), m_buckets.first, nbuckets - 1);
	}
}

template<class Key, class Value, class Alloc>
inline unordered_map<Key, Value, Alloc>::unordered_map(unordered_map&& other)
	: m_size(other.m_size)
{
	_Buff_Structure__move(&m_buckets, &other.m_buckets);
	other.m_size = 0;
}

template<class Key, class Value, class Alloc>
inline unordered_map<Key, Value, Alloc>::~unordered_map() {
	if (m_buckets.first != m_buckets.last)
		clear();
	_Buff_Structure__destroy<pointer, Alloc>(&m_buckets);
}

template<class Key, class Value, class Alloc>
inline unordered_map<Key, Value, Alloc>& unordered_map<Key, Value, Alloc>::operator=(const unordered_map<Key, Value, Alloc>& other) {
	unordered_map<Key, Value, Alloc>(other).swap(*this);
	return *this;
}

template<class Key, class Value, class Alloc>
inline unordered_map<Key, Value, Alloc>& unordered_map<Key, Value, Alloc>::operator=(unordered_map&& other) {
	unordered_map(static_cast<unordered_map&&>(other)).swap(*this);
	return *this;
}

template<class Key, class Value, class Alloc>
inline typename unordered_map<Key, Value, Alloc>::iterator unordered_map<Key, Value, Alloc>::begin() {
	iterator it;
	it.node = *m_buckets.first;
	return it;
}

template<class Key, class Value, class Alloc>
inline typename unordered_map<Key, Value, Alloc>::iterator unordered_map<Key, Value, Alloc>::end() {
	iterator it;
	it.node = 0;
	return it;
}

template<class Key, class Value, class Alloc>
inline typename unordered_map<Key, Value, Alloc>::const_iterator unordered_map<Key, Value, Alloc>::begin() const {
	const_iterator cit;
	cit.node = *m_buckets.first;
	return cit;
}

template<class Key, class Value, class Alloc>
inline typename unordered_map<Key, Value, Alloc>::const_iterator unordered_map<Key, Value, Alloc>::end() const {
	const_iterator cit;
	cit.node = 0;
	return cit;
}

template<class Key, class Value, class Alloc>
inline bool unordered_map<Key, Value, Alloc>::empty() const {
	return m_size == 0;
}

template<class Key, class Value, class Alloc>
inline size_t unordered_map<Key, Value, Alloc>::size() const {
	return m_size;
}

template<class Key, class Value, class Alloc>
inline void unordered_map<Key, Value, Alloc>::clear() {
	pointer it = *m_buckets.first;
	while (it) {
		const pointer next = it->next;
		it->~unordered_hash_node<Key, Value>();
		Alloc::deallocate(it, sizeof(unordered_hash_node<Key, Value>));

		it = next;
	}

	m_buckets.last = m_buckets.first;
	_Buff_Structure__resize<pointer, Alloc>(&m_buckets, 9, 0);
	m_size = 0;
}

template<class Key, class Value, class Alloc>
inline typename unordered_map<Key, Value, Alloc>::iterator unordered_map<Key, Value, Alloc>::find(const Key& key) {
	iterator result;
	result.node = unordered_hash_find(key, m_buckets.first, (size_t)(m_buckets.last - m_buckets.first));
	return result;
}

template<class Key, class Value, class Alloc>
inline typename unordered_map<Key, Value, Alloc>::const_iterator unordered_map<Key, Value, Alloc>::find(const Key& key) const {
	iterator result;
	result.node = unordered_hash_find(key, m_buckets.first, (size_t)(m_buckets.last - m_buckets.first));
	return result;
}

template<class Key, class Value, class Alloc>
inline void unordered_map<Key, Value, Alloc>::rehash(size_t nbuckets) {
	if (m_size + 1 > 4 * nbuckets) {
		pointer root = *m_buckets.first;

		const size_t newnbuckets = ((size_t)(m_buckets.last - m_buckets.first) - 1) * 8;
		m_buckets.last = m_buckets.first;
		_Buff_Structure__resize<pointer, Alloc>(&m_buckets, newnbuckets + 1, 0);
		unordered_hash_node<Key, Value>** buckets = m_buckets.first;

		while (root) {
			const pointer next = root->next;
			root->next = root->prev = 0;
			unordered_hash_node_insert(root, hash(root->first), buckets, newnbuckets);
			root = next;
		}
	}
}

template<class Key, class Value, class Alloc>
inline pair<typename unordered_map<Key, Value, Alloc>::iterator, bool> unordered_map<Key, Value, Alloc>::insert(const pair<Key, Value>& p) {
	pair<iterator, bool> result;
	result.second = false;

	result.first = find(p.first);
	if (result.first.node != 0)
		return result;

	unordered_hash_node<Key, Value>* newnode = new(placeholder(), Alloc::allocate(sizeof(unordered_hash_node<Key, Value>))) unordered_hash_node<Key, Value>(p.first, p.second);
	newnode->next = newnode->prev = 0;

	const size_t nbuckets = (size_t)(m_buckets.last - m_buckets.first);
	unordered_hash_node_insert(newnode, hash(p.first), m_buckets.first, nbuckets - 1);

	++m_size;
	rehash(nbuckets);

	result.first.node = newnode;
	result.second = true;
	return result;
}

template<class Key, class Value, class Alloc>
inline pair<class unordered_map<Key, Value, Alloc>::iterator, bool> unordered_map<Key, Value, Alloc>::emplace(pair<Key, Value>&& p) {
	pair<iterator, bool> result;
	result.second = false;

	result.first = find(p.first);
	if (result.first.node != 0)
		return result;

	const size_t keyhash = hash(p.first);
	unordered_hash_node<Key, Value>* newnode = new(placeholder(), Alloc::allocate(sizeof(unordered_hash_node<Key, Value>))) unordered_hash_node<Key, Value>(static_cast<Key&&>(p.first), static_cast<Value&&>(p.second));
	newnode->next = newnode->prev = 0;

	const size_t nbuckets = (size_t)(m_buckets.last - m_buckets.first);
	unordered_hash_node_insert(newnode, keyhash, m_buckets.first, nbuckets - 1);

	++m_size;
	rehash(nbuckets);

	result.first.node = newnode;
	result.second = true;
	return result;
}

template<class Key, class Value, class Alloc>
inline void unordered_map<Key, Value, Alloc>::erase(const_iterator where) {
	unordered_hash_node_erase(where.node, hash(where->first), m_buckets.first, (size_t)(m_buckets.last - m_buckets.first) - 1);

	where->~unordered_hash_node<Key, Value>();
	Alloc::deallocate((void*)where.node, sizeof(unordered_hash_node<Key, Value>));
	--m_size;
}

template<class Key, class Value, class Alloc>
inline Value& unordered_map<Key, Value, Alloc>::operator[](const Key& key) {
	return insert(pair<Key, Value>(key, Value())).first->second;
}

template<class Key, class Value, class Alloc>
inline void unordered_map<Key, Value, Alloc>::swap(unordered_map& other) {
	size_t tsize = other.m_size;
	other.m_size = m_size, m_size = tsize;
	_Buff_Structure__swap(&m_buckets, &other.m_buckets);
}