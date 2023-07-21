#include <iostream>

#include "SmartPtr.h"

template <typename Ty>
constexpr unique_ptr<Ty>::unique_ptr() noexcept:
	ptr_(nullptr){}

template <typename Ty>
constexpr unique_ptr<Ty>::
	unique_ptr(std::nullptr_t) noexcept :
	unique_ptr(){}

template <typename Ty>
unique_ptr<Ty>::
	unique_ptr(Ty* _pointer) noexcept :
	unique_ptr(){

	ptr_ = _pointer;
}

template <typename Ty>
unique_ptr<Ty>::
	unique_ptr(unique_ptr&& ref) noexcept :
	ptr_(ref.ptr_) {

	ref.ptr_ = nullptr;
}

template <typename Ty>
unique_ptr<Ty>& unique_ptr<Ty>::
	operator=(unique_ptr&& _ref) noexcept {
	if (ptr_ != nullptr) {
		delete ptr_;
	}

	ptr_ = _ref.ptr_;
	_ref.ptr_ = nullptr;

	return *this;
}

template <typename Ty>
unique_ptr<Ty>& unique_ptr<Ty>::
	operator=(std::nullptr_t) noexcept {
	ptr_ = nullptr;

	return *this;
}

template <typename Ty>
template <typename Ty2>
unique_ptr<Ty>& unique_ptr<Ty>::
	operator=(unique_ptr<Ty2>&& _ref) noexcept {
	ptr_ = _ref.ptr_;

	return *this;
}

template <typename Ty>
unique_ptr<Ty>::~unique_ptr() {
	if (get() != nullptr) {
		delete ptr_;
		ptr_ = nullptr;
	}
}

template <typename Ty>
unique_ptr<Ty>::operator bool() const noexcept {

	return ptr_ == nullptr ? false : true;
}

template <typename Ty>
typename std::add_lvalue_reference<Ty>::type
	unique_ptr<Ty>::operator*() const
	noexcept(noexcept(std::declval<Ty_Ptr>())) {

	return *get();
}

template <typename Ty>
typename unique_ptr<Ty>::Ty_Ptr
	unique_ptr<Ty>::operator->() const noexcept {

	return get();
}

template <typename Ty>
bool unique_ptr<Ty>::operator==(const unique_ptr& rhs) const {

	return get() == rhs.get();
}

template <typename Ty>
bool unique_ptr<Ty>::operator>(const unique_ptr& rhs) const {
	return rhs.get() < get();
}

template <typename Ty>
bool unique_ptr<Ty>::operator<(const unique_ptr& rhs) const {
	return get() < rhs.get();
}

template <typename Ty>
bool unique_ptr<Ty>::operator!=(const unique_ptr& rhs) const {
	return !(*this == rhs);
}

template <typename Ty>
bool unique_ptr<Ty>::operator<=(const unique_ptr& rhs) const {
	return !(rhs < *this);
}

template <typename Ty>
bool unique_ptr<Ty>::operator>=(const unique_ptr& rhs) const {
	return !(*this < rhs);
}

template <typename Ty>
Ty* unique_ptr<Ty>::release() noexcept {
	auto _tmp = get();

	ptr_ = nullptr;

	return  _tmp;
}

template <typename Ty>
void unique_ptr<Ty>::
	reset(Ty* _pointer) noexcept {
	ptr_ = _pointer;
}

template <typename Ty>
void unique_ptr<Ty>::
	swap(unique_ptr& _rhs) noexcept {
	auto _tmp = std::move(_rhs);

	_rhs = std::move(*this);
	*this = std::move(_tmp);
}

template <typename Ty>
Ty* unique_ptr<Ty>::get() const noexcept {

	return ptr_;
}

template <typename Ty, typename ..._Args>
unique_ptr<Ty> make_unique(_Args&&... _arg) {

	return unique_ptr<Ty>(new Ty(std::forward<_Args>(_arg)...));
}


template <typename Ty>
constexpr shared_ptr<Ty>::
	shared_ptr() noexcept :
	count_(new size_t(0)),
	ptr_(nullptr){}

template <typename Ty>
constexpr shared_ptr<Ty>::
	shared_ptr(std::nullptr_t) noexcept :
	shared_ptr(){}

template <typename Ty>	
shared_ptr<Ty>::shared_ptr(Ty_Ptr _pointer) :
	shared_ptr() {
	ptr_ = _pointer;
	++(*count_);
}

template <typename Ty>
shared_ptr<Ty>::shared_ptr(const shared_ptr& _other) :
	shared_ptr() {

	ptr_ = _other.ptr_;
	count_ = _other.count_;
	++(*count_);
}

template <typename Ty>
shared_ptr<Ty>& shared_ptr<Ty>::
	operator=(const shared_ptr& _rhs) {

	ptr_ = _rhs.ptr_;
	count_ = _rhs.count_;
	++(*count_);

	return *this;
}

template <typename Ty>
shared_ptr<Ty>::shared_ptr(shared_ptr&& _ref) noexcept :
	shared_ptr(){

	ptr_ = _ref.ptr_;
	count_ = _ref.count_;

	_ref.ptr_ = nullptr;
	_ref.count_ = nullptr;
}

template <typename Ty>
shared_ptr<Ty>& shared_ptr<Ty>::
	operator=(shared_ptr&& _ref) noexcept {
	if (ptr_ != nullptr) {
		delete ptr_;
	}
	if (count_ != nullptr) {
		delete count_;
	}

	ptr_ = _ref.ptr_;
	count_ = _ref.count_;

	_ref.ptr_ = nullptr;
	_ref.count_ = nullptr;
}

template <typename Ty>
shared_ptr<Ty>::~shared_ptr() {
	if (get() == nullptr) {
		(count_ != nullptr) && (delete count_);
		return;
	}

	if (--(*count_) == 0) {
		delete ptr_;
		delete count_;
	}
}

template <typename Ty>
shared_ptr<Ty>::operator bool() const noexcept {

	return ptr_ == nullptr ? false : true;
}

template <typename Ty>
Ty& shared_ptr<Ty>::operator*() const noexcept {

	return *get();
}

template <typename Ty>
typename shared_ptr<Ty>::Ty_Ptr
	shared_ptr<Ty>::operator->() const noexcept {

	return get();
}

template <typename Ty>
typename shared_ptr<Ty>::Ty_Ptr
	shared_ptr<Ty>::get() const noexcept {

	return ptr_;
}

template <typename Ty>
size_t shared_ptr<Ty>::use_count() const noexcept {

	return *count_;
}

template <typename Ty>
bool shared_ptr<Ty>::unique() const noexcept {

	return use_count() == 1 ? true : false;
}

template <typename Ty>
void shared_ptr<Ty>::swap(shared_ptr& _rhs) noexcept {
	auto _tmp = std::move(_rhs);

	_rhs = std::move(*this);
	*this = std::move(_tmp);
}

template <typename Ty>
void shared_ptr<Ty>::reset() {
	reset(nullptr);
}

template <typename Ty>
void shared_ptr<Ty>::reset(Ty_Ptr _pointer) {
	auto tmp(_pointer);

	if(use_count() == 1) {
		delete get();
		delete count_;
	} else {
		--count_;
	}

	*this = std::move(tmp);
}


template <typename Ty, typename ... _Arg>
shared_ptr<Ty> make_shared(_Arg&&... _arg) {

	return shared_ptr<Ty>(new Ty(std::forward<_Arg>(_arg)...));
}

template <typename Ty>
constexpr weak_ptr<Ty>::weak_ptr() noexcept :
	ptr_(nullptr),
	count_(nullptr){}

template <typename Ty>
weak_ptr<Ty>::weak_ptr(const weak_ptr& _other) noexcept :
	weak_ptr(){
	ptr_ = _other.ptr;
	count_ = _other.count_;
}

template <typename Ty>
weak_ptr<Ty>& weak_ptr<Ty>::
	operator=(const weak_ptr& _other) noexcept {
	ptr_ = _other.ptr;
	count_ = _other.count_;

	return *this;
}

template <typename Ty>
weak_ptr<Ty>::weak_ptr(const shared_ptr<Ty> shared_ptr) noexcept :
	weak_ptr(){
	ptr_ = shared_ptr.ptr_;
	count_ = shared_ptr.count_;
}

template <typename Ty>
weak_ptr<Ty>& weak_ptr<Ty>::operator=(weak_ptr&& _ref) noexcept{
	ptr_ = _ref.ptr_;
	count_ = _ref.count_;

	_ref.ptr_ = nullptr;
	_ref.count_ = nullptr;

	return *this;
}

template <typename Ty>
weak_ptr<Ty>::weak_ptr(weak_ptr&& _ref) noexcept :
	weak_ptr(){
	ptr_ = _ref.ptr_;
	count_ = _ref.count_;

	_ref.ptr_ = nullptr;
	_ref.count_ = nullptr;
}

template <typename Ty>
weak_ptr<Ty>::~weak_ptr() {
	ptr_ = nullptr;
	count_ = nullptr;
}
