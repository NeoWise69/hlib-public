/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <static_allocator.hpp>
#include <containers/buffer.hpp>
#include <new.hpp>

HLIB_BEGIN()

/*
* A sequence container that encapsulates dynamic size arrays.
 The elements are stored contiguously, 
 which means that elements can be accessed not only through iterators, 
 but also using offsets to regular pointers to elements. 
 This means that a pointer to an element of a vector may be passed to any function 
 that expects a pointer to an element of an array.
 The storage of the vector is handled automatically, 
 being expanded and contracted as needed. 
 Vectors usually occupy more space than static arrays, 
 because more memory is allocated to handle future growth. 
 This way a vector does not need to reallocate each time an element is inserted, 
 but only when the additional memory is exhausted. 
 The total amount of allocated memory can be queried using capacity() function.
*/
template<class T, class Alloc = HLIB_STATIC_ALLOCATOR>
class _HLIB vector {
public:
	vector();
	vector(const vector& other);
	vector(vector&& other);
	vector(size_t size);
	vector(size_t size, const T& value);
	vector(const T* first, const T* last);
	~vector();
public:
	vector& operator=(const vector& other);
	vector& operator=(vector&& other);
public:
	// Assigns values to the container
	void assign(const T* first, const T* last);

	// Direct access to the underlying array
	const T* data() const;
	// Direct access to the underlying array
	T* data();
	// @returns The number of elements
	size_t size() const;
	// @returns The number of elements that can be held in currently allocated storage
	size_t capacity() const;
	// Checks whether the container is empty
	bool empty() const;

	// Access specified element
	T& operator[](size_t idx);
	// Access specified element
	const T& operator[](size_t idx) const;

	// Access the first element
	const T& front() const;
	// Access the first element
	T& front();
	// Access the last element
	const T& back() const;
	// Access the last element
	T& back();

	// Changes the number of elements stored
	void resize(size_t size);
	// Changes the number of elements stored, and writes into it
	void resize(size_t size, const T& value);
	// Clears the contents
	void clear();
	// Reserves storage
	void reserve(size_t capacity);

	// Adds an element to the end
	void push_back(const T& t);
	// Removes the last element
	void pop_back();

	// Constructs an element in-place at the end
	void emplace_back();
	// Constructs an element in-place at the end
	template<class Param>
	void emplace_back(const Param& param);

	// Reduces memory usage by freeing unused memory
	void shrink_to_fit();

	// Swaps the contents
	void swap(vector& other);
public:
	typedef T value_type;
	typedef T* iterator;
	typedef const T* const_iterator;
public:
	// @returns An iterator to the beginning
	iterator begin();
	// @returns An iterator to the ending
	iterator end();
	// @returns An constant iterator to the beginning
	const_iterator begin() const;
	// @returns An constant iterator to the ending
	const_iterator end() const;
public:
	// Inserts elements
	void insert(iterator where);
	// Inserts elements
	void insert(iterator where, const T& value);
	// Inserts elements
	void insert(iterator where, const T* first, const T* last);
public:
	// Constructs element in-place
	template<class Param >
	void emplace(iterator where, const Param& param);
public:
	// Erases element
	iterator erase(iterator where);
	// Erases elements
	iterator erase(iterator first, iterator last);

	// erases element unordered
	iterator erase_unordered(iterator where);
	// erases elements unordered
	iterator erase_unordered(iterator first, iterator last);
private:
	_Buf_Structure_<T, Alloc> m_buffer;
};

#include <details/vector.inl>

HLIB_END()
