/*
* Copyright 2022 Krivenko Slava
* All rights reserved
*/
#pragma once
#include <macros.hpp>
#include <int.hpp>

HLIB_BEGIN()

HLIB_TEMPLATE1(T)
class unique_ptr {
public:
	unique_ptr() : ptr_(nullptr) {}
	unique_ptr(T* ptr) : ptr_(ptr) {}
	~unique_ptr();
	unique_ptr(unique_ptr const& obj) = delete;
	unique_ptr& operator=(unique_ptr const& obj) = delete;
	unique_ptr(unique_ptr&& die);
	void operator=(unique_ptr&& die);
	T* operator->();
	T& operator*();

private:
	T* ptr_ = nullptr;
	void __cleanup__();
};

HLIB_TEMPLATE2(T, ...Args)
unique_ptr<T> make_unique(Args&& ...args);

HLIB_TEMPLATE1(T)
class unique_ptr<T[]> {
public:
	unique_ptr() : ptr_(nullptr) {}
	unique_ptr(T* ptr) : ptr_(ptr) {}
	~unique_ptr();
	unique_ptr(unique_ptr const& obj) = delete;
	unique_ptr& operator=(unique_ptr const& obj) = delete;
	unique_ptr(unique_ptr&& die);
	void operator=(unique_ptr&& die);
	T* operator->();
	T& operator*();
	T& operator[](i32 pos);
private:
	T* ptr_ = nullptr;
	void __cleanup__();
};

HLIB_TEMPLATE1(T)
class shared_ptr {
public:
	shared_ptr() : ptr_(nullptr), rc_(new u32(0)) {}
	shared_ptr(T* ptr) : ptr_(ptr), rc_(new u32(1)) {}
	shared_ptr(shared_ptr const& obj);
	~shared_ptr();
	shared_ptr& operator=(shared_ptr const& obj);
	shared_ptr(shared_ptr&& die);
	shared_ptr& operator=(shared_ptr&& die);
	u32 count() const { return *rc_; }
	T* get() const { return this->ptr_; }
	T* operator->() const;
	T& operator*() const;
private:
	T* ptr_	= nullptr;
	u32* rc_= nullptr;
	void __cleanup__();
};

HLIB_TEMPLATE1(T)
class shared_ptr<T[]> {
public:
	shared_ptr() : ptr_(nullptr), rc_(new u32(0)) {}
	shared_ptr(T* ptr) : ptr_(ptr), rc_(new u32(1)) {}
	shared_ptr(shared_ptr const& obj);
	~shared_ptr();
	shared_ptr& operator=(shared_ptr const& obj);
	shared_ptr(shared_ptr&& die);
	shared_ptr& operator=(shared_ptr&& die);
	u32 count() const { return *rc_; }
	T* get() const { return this->ptr_; }
	T* operator->() const;
	T& operator*() const;
	T& operator[](i32 pos);
private:
	T* ptr_	= nullptr;
	u32* rc_= nullptr;
	void __cleanup__();
};

HLIB_TEMPLATE2(T, ...Args)
shared_ptr<T> make_shared(Args&& ...args);

#include <details/smart_ptr.inl>

HLIB_END()
