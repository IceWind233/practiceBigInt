#ifndef _SMARTPTR_H_
#define _SMARTPTR_H_

#include <iostream>
#include <cstddef>

template<typename Ty>
class unique_ptr {

	typedef Ty* Ty_Ptr;

public:

	constexpr unique_ptr() noexcept;

	constexpr unique_ptr(std::nullptr_t) noexcept;

	explicit unique_ptr(Ty_Ptr _pointer) noexcept;

	unique_ptr(unique_ptr&& _ref) noexcept;

	unique_ptr& operator=(unique_ptr&& _ref) noexcept;

	unique_ptr& operator=(std::nullptr_t) noexcept;

	template <typename Ty2>
	unique_ptr& operator=(unique_ptr<Ty2>&& _ref) noexcept;

	~unique_ptr();

public:

	explicit operator bool() const noexcept;

	typename std::add_lvalue_reference<Ty>::type
		operator*() const noexcept(noexcept(std::declval<Ty_Ptr>()));

	Ty_Ptr operator->() const noexcept;

	bool operator==(const unique_ptr& rhs) const;

	bool operator>(const unique_ptr& rhs) const;

	bool operator<(const unique_ptr& rhs) const;

	bool operator!=(const unique_ptr& rhs) const;

	bool operator<=(const unique_ptr& rhs) const;

	bool operator>=(const unique_ptr& rhs) const;

	friend std::ostream& operator<<(std::ostream& os, unique_ptr<Ty>& rhs) {
		os << rhs.get();

		return os;
	}

public:

	Ty_Ptr release() noexcept;

	void reset(Ty_Ptr _pointer) noexcept;

	void swap(unique_ptr& _rhs) noexcept;

	Ty_Ptr get() const noexcept;

private:

	Ty_Ptr ptr_;

};

template <typename Ty, typename ..._Args>
unique_ptr<Ty> make_unique(_Args&& ..._arg);

template <typename Ty>
class shared_ptr {

	typedef Ty* Ty_Ptr;

public:

	constexpr shared_ptr() noexcept;

	constexpr shared_ptr(std::nullptr_t) noexcept;

	explicit shared_ptr(Ty_Ptr _pointer);

	shared_ptr(const shared_ptr& _other);

	shared_ptr& operator=(const shared_ptr& _rhs);

	shared_ptr(shared_ptr&& _ref) noexcept;

	shared_ptr& operator=(shared_ptr&& _ref) noexcept;

	~shared_ptr();

public:

	explicit operator bool() const noexcept;

	Ty& operator*() const noexcept;

	Ty_Ptr operator->() const noexcept;

public:

	Ty_Ptr get() const noexcept;

	size_t use_count() const noexcept;

	bool unique() const noexcept;

	void swap(shared_ptr& _rhs) noexcept;

	void reset();

	void reset(Ty_Ptr _pointer);

private:

	size_t* count_;
	Ty* ptr_;

};

template <typename Ty, typename ..._Arg>
shared_ptr<Ty> make_shared(_Arg&& ..._arg);

template <typename Ty>
class weak_ptr {

	typedef Ty* Ty_Ptr;

public:

	constexpr weak_ptr() noexcept;

	weak_ptr(const weak_ptr& _other) noexcept;

	weak_ptr& operator=(const weak_ptr& _other) noexcept;

	explicit weak_ptr(const shared_ptr<Ty> shared_ptr) noexcept;

	weak_ptr& operator=(weak_ptr&& _ref) noexcept;

	weak_ptr(weak_ptr&& _ref) noexcept;

	~weak_ptr();

public:

	void swap(weak_ptr& rhs);

	void reset();

public:
	Ty_Ptr ptr_;
	size_t* count_;

};


#endif
