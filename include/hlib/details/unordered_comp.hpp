/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <traits.hpp>
#include <int.hpp>

HLIB_BEGIN()

template<class Key, class Val>
struct unordered_hash_node {
	unordered_hash_node(const Key& key, const Val& value);
	unordered_hash_node(Key&& key, Val&& value);

	const Key first;
	Val second;
	unordered_hash_node* next;
	unordered_hash_node* prev;

private:
	unordered_hash_node& operator=(const unordered_hash_node&);
};

template<class Key>
struct unordered_hash_node<Key, void> {
	explicit unordered_hash_node(const Key& key);
	explicit unordered_hash_node(Key&& key);

	const Key first;
	unordered_hash_node* next;
	unordered_hash_node* prev;

private:
	unordered_hash_node& operator=(const unordered_hash_node&);
};

template<class Node>
struct unordered_hash_iterator {
	Node* operator->() const;
	Node& operator*() const;
	Node* node;
};

template<class Node>
struct unordered_hash_iterator<const Node> {
	unordered_hash_iterator() {}
	unordered_hash_iterator(unordered_hash_iterator<Node> other)
		: node(other.node)
	{}

	const Node* operator->() const;
	const Node& operator*() const;
	const Node* node;
};

template<class Key>
struct unordered_hash_iterator<const unordered_hash_node<Key, void>> {
	const Key* operator->() const;
	const Key& operator*() const;
	unordered_hash_node<Key, void>* node;
};

template<class Key, class Val>
static inline void unordered_hash_node_insert(unordered_hash_node<Key, Val>* node, size_t hash, unordered_hash_node<Key, Val>** buckets, size_t nbuckets);

template<class Key, class Val>
static inline void unordered_hash_node_erase(const unordered_hash_node<Key, Val>* where, size_t hash, unordered_hash_node<Key, Val>** buckets, size_t nbuckets);

template<class LNode, class RNode>
static inline bool operator==(const unordered_hash_iterator<LNode>& lhs, const unordered_hash_iterator<RNode>& rhs);

template<class LNode, class RNode>
static inline bool operator!=(const unordered_hash_iterator<LNode>& lhs, const unordered_hash_iterator<RNode>& rhs);

template<class Node>
static inline void operator++(unordered_hash_iterator<Node>& lhs);

template<class Node, class Key>
static inline Node unordered_hash_find(const Key& key, Node* buckets, size_t nbuckets);

#include <details/unordered_comp.inl>

HLIB_END()
