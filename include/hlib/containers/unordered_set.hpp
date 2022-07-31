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
 Unordered set is an associative container that contains a set of unique objects of type Key. 
 Search, insertion, and removal have average constant-time complexity.
 Internally, the elements are not sorted in any particular order, but organized into buckets. 
 Which bucket an element is placed into depends entirely on the hash of its value. 
 This allows fast access to individual elements, since once a hash is computed, 
 it refers to the exact bucket the element is placed into.
 ---
 Container elements may not be modified (even by non const iterators) since modification could change 
 an element's hash and corrupt the container.
*/
template<class Key, class Alloc = HLIB_STATIC_ALLOCATOR>
class _HLIB unordered_set {
public:
	unordered_set();
	unordered_set(const unordered_set& other);
	unordered_set(unordered_set&& other);
	~unordered_set();
public:
	unordered_set& operator=(const unordered_set& other);
	unordered_set& operator=(unordered_set&& other);
public:
	typedef unordered_hash_iterator<const unordered_hash_node<Key, void> > const_iterator;
	typedef const_iterator iterator;
public:
	// @returns An iterator to the beginning
	iterator begin() const;
	// @returns An iterator to the end
	iterator end() const;
public:
	// Clears the contents
	void clear();
	// Checks whether the container is empty
	bool empty() const;
	// @returns The number of elements
	size_t size() const;
public:
	// Finds element with specific key
	iterator find(const Key& key) const;
	// Inserts elements
	pair<iterator, bool> insert(const Key& key);
	// Constructs element in-place
	pair<iterator, bool> emplace(Key&& key);
	// Erases elements
	void erase(iterator where);
	// Erases elements, returns 1 if operation successful
	size_t erase(const Key& key);

	// Swaps the contents
	void swap(unordered_set& other);
private:
	void rehash(size_t nbuckets);

	typedef unordered_hash_node<Key, void>* pointer;

	size_t m_size;
	_Buf_Structure_<pointer, Alloc> m_buckets;
};

#include <details/unordered_set.inl>

HLIB_END()
