#pragma once
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <memory>
#include <cassert>
#include <utility>

template<typename T>
class FastVec {
	T* data_;
	uint32_t size_ {}, capacity_ {};

public:
	FastVec() {
		// Do nothing
	}

	FastVec(std::initializer_list<T> l) {
		reserve(l.size());
		for (uint32_t i=0; i<l.size(); i++) {
			push_back(*(l.data()+i));
		}
	}

	// Copy constructor
	FastVec(FastVec const& o) {
		reserve(o.capacity());
		for (uint32_t i=0; i<o.size(); i++) {
			new (data+i) T(o[i]);
		}
		size_ = o.size;
	}

	// Move constructor
	FastVec(FastVec&& o) {
		*this = o;
	}

	FastVec& operator=(FastVec&& o) {
		erase();
		data_ = o.data_;
		size_ = o.size_;
		capacity_ = o.capacity_;

		o.data_ = nullptr;
		o.size_ = 0;
		o.capacity_ = 0;
		return *this;
	}

	T& operator[](uint32_t index) {
		assert(index < size_);
		return data_[index];
	}

	T const& operator[](uint32_t index) const {
		assert(index < size_);
		return data_[index];
	}

	void reserve(uint32_t qty) {
		T* new_data = reinterpret_cast<T*>(new std::aligned_storage_t<sizeof(T), alignof(T)>[qty]);
		assert(qty >= size_);

		if (data_) {
			// Move all elements to the new data
			for (uint32_t i=0; i<size_; i++) {
				new (new_data+i) T (std::move(data_[i]));
				(data_+i)->~T();
			}
			delete [] data_;
		}

		capacity_ = qty;
		data_ = new_data;
	}

	void grow() {
		if (!capacity_) capacity_ = 4;
		reserve(capacity_ * 2);
	}

	T* data() {
		return data_;
	}

	T const* data() const {
		return data;
	}

	void push_back(const T& value) {
		if (size_ == capacity_) grow();
		new (data_+size_++) T(value);
	}

	T pop_back() {
		assert(size_);
		return data_[--size_];
	}

	template<typename... Ts>
	T& emplace_back(Ts&&... args) {
		if (size_ == capacity_) grow();
		return *(new (data_+size_++) T (std::forward<Ts>(args)...));
	}

	void erase() {
		for (; size_>0; size_--) {
			(end()-1)->~T();
		}
		if (data_) delete [] data_;
		capacity_ = 0;
	}

	auto size() const {
		return size_;
	}

	T* begin() {
		return data_;
	}

	T const* cbegin() const {
		return data_;
	}

	T* end() {
		return data_+size_;
	}

	T const* cend() const {
		return data_+size_;
	}

	auto capacity() const {
		return capacity_;
	}

	friend std::ostream& operator<<(std::ostream& os, FastVec const& fv) {
		os << "[";
		for (uint32_t i=0; i<fv.size(); i++) {
			os << fv[i];
			if (i < fv.size()-1) os << ", ";
		}
		os << "]" << std::endl;
		return os;
	}
};

