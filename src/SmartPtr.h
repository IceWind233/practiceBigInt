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

	constexpr unique_ptr(Ty_Ptr _pointer) noexcept;

	unique_ptr(unique_ptr&& _ref) noexcept;

	unique_ptr& operator=(unique_ptr&& _ref) noexcept;

	unique_ptr& operator=(std::nullptr_t) noexcept;

	template <typename Ty2>
	unique_ptr& operator=(unique_ptr<Ty2>&& _ref) noexcept;

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

#endif
