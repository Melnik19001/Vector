#pragma once

#include <algorithm>
#include <cstdio>
#include <memory>
#include "VectorExceptions.cpp"

using namespace std;

template <typename T>
class Vector {

	protected:
		T* array_begin_ptr_;
		size_t size_;
		size_t capacity_;

	public:

//constructors&destructors
		Vector();
		Vector(const Vector <T> &object);
		~Vector();

//iterators
		T* begin() const;
		T* end() const;

//capacity
		bool empty() const;
		int size() const;
		int capacity() const;
		void reserve(const int necessary_len);

//element access
		T& operator [] (const int id);
		T& at(const int id);

//modifiers&operators
		void clear();
		void push_back(const T &new_value);
		void pop_back();
		Vector <T>& operator = (const Vector <T> &object);

//friend functions
		friend void swap(Vector <T> &x, Vector <T> &y);
};

template <typename T>
Vector <T>::Vector() {
	array_begin_ptr_ = nullptr;
	size_ = capacity_ = 0;
}

template <typename T>
Vector <T>::Vector(const Vector <T> &object) {
	array_begin_ptr_ = new T[object.size()];
	size_ = object.size();
	capacity_ = object.capacity();
	for (int i = 0; i < size_; ++i)
		array_begin_ptr_[i] = object[i];
}

template <typename T>
Vector <T>::~Vector() {
	delete [] this -> array_begin_ptr_;
}

template <typename T>
T* Vector <T>::begin() const {
	return this -> array_begin_ptr_;
}

template <typename T>
T* Vector <T>::end() const {
	return this -> array_begin_ptr_ + this -> size_;
}

template <typename T>
bool Vector <T>::empty() const {
	return !this -> size_;
}

template <typename T>
int Vector <T>::size() const {
	return this -> size_;
}

template <typename T> 
int Vector <T>::capacity() const {
	return this -> capacity_;
}

template <typename T>
void Vector <T>::reserve(const int necessary_len) {
	if (this -> capacity_ >= necessary_len)
		return;

	T* new_ptr_ = new T[necessary_len];
	for (size_t i = 0; i < this -> size_; ++i)
		new_ptr_[i] = this -> array_begin_ptr_[i];
	delete [] this -> array_begin_ptr_;
	this -> array_begin_ptr_ = new_ptr_;
	this -> capacity_ = necessary_len;
}

template <typename T>
T& Vector <T>::operator [] (const int id) {
	return this -> array_begin_ptr_[id];
}

template <typename T>
T& Vector <T>::at(const int id) {
	if (id < 0 || id >= this -> size_)
		throw OutOfRangeException();
	return this -> array_begin_ptr_[id];
}

template <typename T>
void Vector <T>::clear() {
	this -> size_ = 0;
}

template <typename T>
void Vector <T>::push_back(const T &new_value) {
	if (this -> size_ == this -> capacity_) {
		if (!this -> capacity_)
			this -> capacity_ = 1;
		else
			this -> capacity_ *= 2;
		T* new_ptr_ = new T[this -> capacity_];
		for (size_t i = 0; i < this -> size_; ++i)
			new_ptr_[i] = this -> array_begin_ptr_[i];
		delete [] this -> array_begin_ptr_;
		this -> array_begin_ptr_ = new_ptr_;
	}

	this -> array_begin_ptr_[this -> size_] = new_value;
	++this -> size_;
}

template <typename T> 
void Vector <T>::pop_back() {
	--this -> size_;
}

template <typename T>
Vector <T>& Vector <T>::operator = (const Vector <T> &object) {
	Vector <T> res = Vector <T> (object);
	swap(res, *this);
	return *this;
}

template <typename T>
void swap(Vector <T> x, Vector <T> y) {
	swap(x.array_begin_ptr_, y.array_begin_ptr_);
	swap(x.size_, y.size_);
	swap(x.capacity_, y.capacity_);
}
