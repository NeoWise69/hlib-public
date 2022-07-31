template<class T>
inline void unique_ptr<T>::__cleanup__() {
	if (this->ptr_ != nullptr)
		delete this->ptr_;
}

template<class T>
inline unique_ptr<T>::~unique_ptr() {
	__cleanup__();
}

template<class T>
inline unique_ptr<T>::unique_ptr(unique_ptr&& die) {
	this->ptr_ = die.ptr_;
	die.ptr_ = nullptr;
}

template<class T>
inline void unique_ptr<T>::operator=(unique_ptr&& die) {
	__cleanup__();
	this->ptr_ = die.ptr_;
	die.ptr_ = nullptr;
}

template<class T>
inline T* unique_ptr<T>::operator->() {
	return this->ptr_;
}

template<class T>
inline T& unique_ptr<T>::operator*() {
	return *(this->ptr_);
}

template<class T>
inline void unique_ptr<T[]>::__cleanup__() {
	if (this->ptr_ != nullptr)
		delete this->ptr_;
}

template<class T>
inline unique_ptr<T[]>::~unique_ptr() {
	__cleanup__();
}

template<class T>
inline unique_ptr<T[]>::unique_ptr(unique_ptr&& die) {
	this->ptr_ = die.ptr_;
	die.ptr_ = nullptr;
}

template<class T>
inline void unique_ptr<T[]>::operator=(unique_ptr&& die) {
	__cleanup__();
	this->ptr_ = die.ptr_;
	die.ptr_ = nullptr;
}

template<class T>
inline T* unique_ptr<T[]>::operator->() {
	return this->ptr_;
}

template<class T>
inline T& unique_ptr<T[]>::operator*() {
	return *(this->ptr_);
}

template<class T>
inline T& unique_ptr<T[]>::operator[](i32 pos) {
	if (pos < 0) {
		HLIB_DEBUGBREAK();
	}
	return this->ptr_[pos];
}

#include <utility.hpp>
#include "..\memory\smart_ptr.hpp"

template<class T, class ...Args>
inline unique_ptr<T> make_unique(Args&& ...args)
{
	return unique_ptr<T>(new T(hlib::forward<Args&&>(args)...));
}


template<class T, class ...Args>
inline shared_ptr<T> make_shared(Args && ...args)
{
	return shared_ptr<T>(new T(hlib::forward<Args&&>(args)...));
}


template<class T, class ...Args>
inline unique_ptr<T[]> make_unique(Args&& ...args)
{
	return unique_ptr<T[]>(new T(hlib::forward<Args&&>(args)...));
}


template<class T>
inline shared_ptr<T>::shared_ptr(shared_ptr const& obj)
{
	this->ptr_ = obj.ptr_;
	this->rc_ = obj.rc_;
	if (nullptr != obj.ptr_)
		(*this->rc_)++;
}

template<class T>
inline shared_ptr<T>::~shared_ptr()
{
	__cleanup__();
}

template<class T>
inline shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr const& obj)
{
	__cleanup__();

	this->ptr_ = obj.ptr_;
	this->rc_ = obj.rc_;
	if (nullptr != obj.ptr_)
		(*this->rc_)++;
}

template<class T>
inline shared_ptr<T>::shared_ptr(shared_ptr&& die)
{
	this->ptr_ = die.ptr_;
	this->rc_ = die.rc_;
	die.ptr_ = nullptr;
	die.rc_ = nullptr;
}

template<class T>
inline shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& die)
{
	__cleanup__();

	this->ptr_ = die.ptr_;
	this->rc_ = die.rc_;
	die.ptr_ = nullptr;
	die.rc_ = nullptr;
}

template<class T>
inline T* shared_ptr<T>::operator->() const 
{
	return this->ptr_;
}

template<class T>
inline T& shared_ptr<T>::operator*() const 
{
	return this->ptr_;
}

template<class T>
inline T& shared_ptr<T[]>::operator[](i32 pos)
{
	if (pos < 0)
		HLIB_DEBUGBREAK();

	return this->ptr_[pos];
}

template<class T>
inline void shared_ptr<T>::__cleanup__()
{
	(*rc_)--;
	if (*rc_ == 0)
		if (nullptr != ptr_)
			delete ptr_;
}
