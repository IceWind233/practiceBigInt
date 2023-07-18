#include <iostream>
#include <xutility>
#include "MyVector.h"


template <typename T>
vector<T>::vector() :
	size_(0),
	capacity_(0),
	array(nullptr) {}

template <typename T>
vector<T>::vector(size_t _num, const T& _val) :
	vector() {
	for (auto i = 0; i < _num; ++i) {
		push_back(_val);
	}
}

template <typename T>
vector<T>::vector(iterator _first, iterator _last) :
	vector() {

	insert(begin(), _first, _last);
}

template <typename T>
constexpr vector<T>::vector(std::initializer_list<T> init) :
	vector() {

	for (auto idx : init) {
		push_back(idx);
	}
}

template <typename T>
vector<T>::vector(const vector& other) :
	size_(0),
	capacity_(other.capacity()),
	array(nullptr) {

	reserve(other.capacity());

	for (auto i = 0; i < other.size(); ++i) {
		push_back(other.array[i]);
	}
}

template <typename T>
vector<T>::vector(size_t _num) :
	vector(_num, T()){}

template <typename T>
vector<T>& vector<T>::operator=(vector& other) {

	clear();
	insert(begin(), other.begin(), other.end());

	return *this;
}

template <typename T>
vector<T>::vector(vector&& vector_ref) noexcept :
	size_(vector_ref.size()),
	capacity_(vector_ref.capacity()) {

	array = vector_ref.array;
	vector_ref.array = nullptr;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& vector_ref) noexcept {
	free(array);
	array = vector_ref.array;
	size_ = vector_ref.size();
	capacity_ = vector_ref.capacity();

	vector_ref.array = nullptr;
	vector_ref.size_ = 0;
	vector_ref.capacity_ = 0;

	return *this;
}

template <typename T>
vector<T>::~vector() {

	delete[] array;
}

template <typename T>
T& vector<T>::operator[](size_t idx) {

	return array[idx];
}

template <typename T>
constexpr T& vector<T>::operator[](size_t idx) const {

	return array[idx];
}

template <typename T>
T& vector<T>::at(size_t idx) {

	return array[idx];
}

template <typename T>
T& vector<T>::front() {

	return array[0];
}

template <typename T>
T& vector<T>::back() {

	return array[size() - 1];
}

template <typename T>
bool vector<T>::empty() const {

	return size_ == 0 ? true : false;
}

template <typename T>
size_t vector<T>::size() const {

	return size_;
}

template <typename T>
size_t vector<T>::capacity() const {

	return capacity_;
}

template <typename T>
void vector<T>::push_back(const T& element) {
	emplace_back(element);
}

template <typename T>
void vector<T>::push_back(T&& element) {

	emplace_back(std::move(element));
}

template <typename T>
template <typename ... Arg>
void vector<T>::emplace_back(Arg&&... arg) {
	if (check_full()) {
		reserve(2 * capacity());
	}

	array[size_] = T(std::forward<Arg>(arg)...);
	++size_;
}

template <typename T>
void vector<T>::pop_back() {
	if (size() > 0)
		--size_;
}

template <typename T>
void vector<T>::reserve(const size_t new_size) {
	if (new_size < capacity()) {

		return;
	}

	capacity_ = (new_size == 0 ? 1 : new_size);

	auto *new_array = new T[capacity()];

	if (array != nullptr) {
		for (auto i = 0; i < size(); ++i) {
			new_array[i] = array[i];
		}
		delete[] array;
	}

	array = new_array;
}

template <typename T>
void vector<T>::resize(size_t new_size) {
	if (new_size <= size()) {
		size_ = new_size;

		return;
	}

	for (auto i = size(); i < new_size; ++i) {
		push_back(T());
	}
}

template <typename T>
void vector<T>::clear() {

	free(array);
	array = new T[capacity()];
	size_ = 0;
}

template <typename T>
void vector<T>::swap(vector& other) noexcept {
	vector tmp = std::move(*this);

	*this = std::move(other);
	other = std::move(tmp);
}

template <typename T>
void vector<T>::assign(std::initializer_list<T> init) {

	vector<T> _tmp(init);

	*this = std::move(_tmp);
}

template <typename T>
void vector<T>::assign(iterator _first, iterator _last) {

	vector<T> _tmp(_first, _last);

	*this = std::move(_tmp);
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(iterator pos) {

	return erase(pos, pos + 1);
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(iterator _first, iterator _last) {

	auto offset = _last - _first;

	for (auto &it = _last; it != end(); ++it) {
		*(it - offset) = *it;
	}

	size_ -= offset;

	return _last - offset;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(
	const iterator	_pos,
	const T&		_value) {

	vector<T> _tmp({ _value });

	return insert(_pos, _tmp.begin(), _tmp.end());
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(
	const	iterator _begin,
			iterator _first,
			iterator _last) {

	auto _offset = _last - _first;
	auto _diff = _begin - begin();

	while (size() + _offset >= capacity()) {
		reserve(2 * capacity());
	}

	auto current_pos = begin() + _diff;

	for (auto it = std::prev(end()); it != std::prev(current_pos); --it) {
		*(it + _offset) = *it;
	}

	size_ += _offset;

	for (auto i = 0; i < _offset; ++i) {
		*(current_pos + i) = *(_first + i);
	}

	return begin() + _diff;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(
	const iterator	 _pos,
		  size_t	 _num,
	const T&		 _val) {

	vector<T> tmp(_num, _val);

	return insert(_pos, tmp.begin(), tmp.end());
}


template <typename T>
template <typename ... Arg>
typename vector<T>::iterator vector<T>::emplace(
	iterator _pos, 
	Arg&&... arg) {

	T tmp(std::forward<Arg>(arg)...);

	return insert(_pos, tmp);;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {

	return iterator(array);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {

	return iterator(array + size());
}

template <typename T>
bool vector<T>::check_full() const {

	return size_ >= capacity() ? true : false;
}

template <typename T>
bool vector<T>::iterator::operator==(const iterator& other) const {

	return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator!=(const iterator& other) const {

	return !(*this == other);
}

template <typename T>
T& vector<T>::iterator::operator*() const {

	return *ptr_;
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator++() {
	++ptr_;

	return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator++(int) {
	iterator temp = *this;

	++ptr_;

	return temp;
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator--() {
	--ptr_;

	return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator--(int) {
	iterator temp = *this;

	--ptr_;

	return temp;
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator+=(size_t n) {
	ptr_ += n;

	return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator+(size_t n) const {

	return iterator(ptr_ + n);
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator-=(size_t n) {
	ptr_ -= n;

	return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator-(size_t n) const {

	return iterator(ptr_ - n);
}

template <typename T>
size_t vector<T>::iterator::operator-(const iterator& other) const {

	return ptr_ - other.ptr_;
}

template <typename T>
T& vector<T>::iterator::operator[](size_t n) const {

	return *(ptr_ + n);
}

template <typename T>
bool vector<T>::iterator::operator<(const iterator& other) const {

	return ptr_ < other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator>(const iterator& other) const {

	return ptr_ > other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator<=(const iterator& other) const {

	return ptr_ <= other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator>=(const iterator& other) const {

	return ptr_ >= other.ptr_;
}