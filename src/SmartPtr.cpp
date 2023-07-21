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
constexpr unique_ptr<Ty>::
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
