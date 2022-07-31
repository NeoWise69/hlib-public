template<class Key, class Val>
inline unordered_hash_node<Key, Val>::unordered_hash_node(const Key& key, const Val& value)
	: first(key)
	, second(value)
{}

template<class Key, class Val>
inline unordered_hash_node<Key, Val>::unordered_hash_node(Key&& key, Val&& value)
	: first(static_cast<Key&&>(key))
	, second(static_cast<Val&&>(value))
{}

template<class Key>
inline unordered_hash_node<Key, void>::unordered_hash_node(const Key& key)
	: first(key)
{}

template<class Key>
inline unordered_hash_node<Key, void>::unordered_hash_node(Key&& key)
	: first(static_cast<Key&&>(key))
{}

template<class Key, class Val>
inline void unordered_hash_node_insert(unordered_hash_node<Key, Val>* node, size_t hash, unordered_hash_node<Key, Val>** buckets, size_t nbuckets) {
	size_t bucket = hash & (nbuckets - 1);

	unordered_hash_node<Key, Val>* it = buckets[bucket + 1];
	node->next = it;
	if (it) {
		node->prev = it->prev;
		it->prev = node;
		if (node->prev)
			node->prev->next = node;
	}
	else {
		size_t newbucket = bucket;
		while (newbucket && !buckets[newbucket])
			--newbucket;

		unordered_hash_node<Key, Val>* prev = buckets[newbucket];
		while (prev && prev->next)
			prev = prev->next;

		node->prev = prev;
		if (prev)
			prev->next = node;
	}

	// propagate node through buckets
	for (; it == buckets[bucket]; --bucket) {
		buckets[bucket] = node;
		if (!bucket)
			break;
	}
}

template<class Key, class Val>
inline void unordered_hash_node_erase(const unordered_hash_node<Key, Val>* where, size_t hash, unordered_hash_node<Key, Val>** buckets, size_t nbuckets) {
	size_t bucket = hash & (nbuckets - 1);

	unordered_hash_node<Key, Val>* next = where->next;
	for (; buckets[bucket] == where; --bucket) {
		buckets[bucket] = next;
		if (!bucket)
			break;
	}

	if (where->prev)
		where->prev->next = where->next;
	if (next)
		next->prev = where->prev;
}

template<class LNode, class RNode>
inline bool operator==(const unordered_hash_iterator<LNode>& lhs, const unordered_hash_iterator<RNode>& rhs) {
	return lhs.node == rhs.node;
}

template<class LNode, class RNode>
inline bool operator!=(const unordered_hash_iterator<LNode>& lhs, const unordered_hash_iterator<RNode>& rhs) {
	return lhs.node != rhs.node;
}

template<class Node>
inline void operator++(unordered_hash_iterator<Node>& lhs) {
	lhs.node = lhs.node->next;
}

template<class Node>
inline Node* unordered_hash_iterator<Node>::operator->() const {
	return node;
}

template<class Node>
inline Node& unordered_hash_iterator<Node>::operator*() const {
	return *node;
}

template<class Node>
inline const Node* unordered_hash_iterator<const Node>::operator->() const {
	return node;
}

template<class Node>
inline const Node& unordered_hash_iterator<const Node>::operator*() const {
	return *node;
}

template<class Key>
inline const Key* unordered_hash_iterator<const unordered_hash_node<Key, void> >::operator->() const {
	return &node->first;
}

template<class Key>
inline const Key& unordered_hash_iterator<const unordered_hash_node<Key, void> >::operator*() const {
	return node->first;
}

template<class Node, class Key>
inline Node unordered_hash_find(const Key& key, Node* buckets, size_t nbuckets) {
	const size_t bucket = hash(key) & (nbuckets - 2);
	for (Node it = buckets[bucket], end = buckets[bucket + 1]; it != end; it = it->next)
		if (it->first == key)
			return it;

	return 0;
}
