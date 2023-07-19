
#ifndef _MYVECTOR_H_
#define _MYVECTOR_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include <xutility>


template<typename T>
class vector {

public:

	class iterator :
		public std::iterator<
		std::random_access_iterator_tag,
		vector> {

	public:

		explicit iterator(T* ptr) : ptr_(ptr) {}

	public:

		T& operator*() const;

		T& operator[](size_t) const;

		iterator& operator++();

		iterator operator++(int);

		iterator& operator--();

		iterator operator--(int);

		iterator& operator+=(size_t);

		iterator operator+(size_t) const;

		iterator& operator-=(size_t);

		iterator operator-(size_t) const;

		size_t operator-(const iterator&) const;

		bool operator==(const iterator&) const;

		bool operator!=(const iterator&) const;

		bool operator<(const iterator&) const;

		bool operator>(const iterator&) const;

		bool operator<=(const iterator&) const;

		bool operator>=(const iterator&) const;

	private:

		T* ptr_;
	};

public:

	vector();

	vector(const vector&);

	explicit vector(size_t);

	vector(size_t, const T&);

	vector(iterator, iterator);

	constexpr vector(std::initializer_list<T>);

	vector& operator=(vector&);

	vector(vector&&) noexcept;

	vector& operator=(vector&&) noexcept;

	~vector();

public:

	T& operator[](size_t);

	constexpr T& operator[](size_t) const;

	friend std::ostream& operator<<(std::ostream& os, vector& vec) {
		for (auto it : vec) {
			os << it << " ";
		}
		os << std::endl;

		return os;
	}

public:

	T& at(size_t);

	T& front();

	T& back();

	bool empty() const;

	size_t size() const;

	size_t capacity() const;

	void push_back(const T&);

	void push_back(T&&);

	template <typename ...Arg>
	void emplace_back(Arg&& ...arg);

	void pop_back();

	void reserve(size_t);

	void resize(size_t);

	void clear();

	void swap(vector&) noexcept;

	void assign(std::initializer_list<T>);

	void assign(iterator, iterator);

	iterator begin();

	iterator end();

	iterator erase(iterator);

	iterator erase(iterator, iterator);

	iterator insert(const iterator, const T&);

	iterator insert(const iterator, size_t, const T&);

	iterator insert(const iterator, iterator, iterator);

	template<typename ...Arg>
	iterator emplace(iterator, Arg&& ...arg);


private:

	T* array;
	size_t size_;
	size_t capacity_;

private:

	bool check_full() const;

	void destroy_array();

};

#endif