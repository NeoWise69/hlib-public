/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <hash.hpp>
#include <pair.hpp>
#include <static_allocator.hpp>
#include <containers/buffer.hpp>
#include <details/unordered_comp.hpp>

HLIB_BEGIN()

/*
  Unordered map is an associative container that contains key-value pairs with unique keys.
* Search, insertion, and removal of elements have average constant-time complexity.
* Internally, the elements are not sorted in any particular order, but organized into buckets. 
  Which bucket an element is placed into depends entirely on the hash of its key. 
  Keys with the same hash code appear in the same bucket. 
  This allows fast access to individual elements, since once the hash is computed, 
  it refers to the exact bucket the element is placed into.
*/
template<class Key, class Value, class Alloc = HLIB_STATIC_ALLOCATOR>
class _HLIB unordered_map {
public:
	unordered_map();
	unordered_map(const unordered_map& other);
	unordered_map(unordered_map&& other);
	~unordered_map();
public:
	unordered_map& operator=(const unordered_map& other);
	unordered_map& operator=(unordered_map&& other);
public:
	typedef pair<Key, Value> value_type;
public:
	typedef unordered_hash_iterator<const unordered_hash_node<Key, Value> > const_iterator;
	typedef unordered_hash_iterator<unordered_hash_node<Key, Value> > iterator;
public:
	// @returns An iterator to the beginning
	iterator begin();
	// @returns An iterator to the end
	iterator end();

	// @returns A constant iterator to the beginning
	const_iterator begin() const;
	// @returns A constant iterator to the end
	const_iterator end() const;
public:
	// Clears the contents
	void clear();
	// Checks whether the container is empty
	bool empty() const;
	// @returns The number of elements
	size_t size() const;
public:
	// Finds element with specific key, and returns constant iterator to it
	const_iterator find(const Key& key) const;
	// Finds element with specific key, and returns iterator to it
	iterator find(const Key& key);
	// Inserts elements
	pair<iterator, bool> insert(const pair<Key, Value>& p);
	// Constructs element in-place
	pair<iterator, bool> emplace(pair<Key, Value>&& p);
	// Erases elements
	void erase(const_iterator where);

	// Access or insert specified element
	Value& operator[](const Key& key);

	// Swaps the contents
	void swap(unordered_map& other);
private:
	void rehash(size_t nbuckets);

	typedef unordered_hash_node<Key, Value>* pointer;

	size_t m_size;
	_Buf_Structure_<pointer, Alloc> m_buckets;
};

#include <details/unordered_map.inl>

HLIB_END()
