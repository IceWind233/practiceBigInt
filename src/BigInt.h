
#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <array>
#include <cstdint>
#include <iostream>

class BigInt {
public:
	static constexpr size_t kMaxLen = 256;

	typedef std::array<uint8_t, kMaxLen> buffer_t;

	typedef enum _same_flag_t {
		kIsSame = 0,
		kLhsBigger = 1,
		kRhsBigger = -1,

	} same_flag_t;

public:
	BigInt();

	BigInt(const char*, size_t);

	BigInt(int64_t);

	BigInt(uint64_t);

	BigInt(int);

	BigInt(const BigInt&) = default;

	BigInt& operator=(const BigInt&) = default;

	BigInt(BigInt&&) noexcept = default;

	BigInt& operator=(BigInt&&) noexcept = default;

	~BigInt() = default;

public:
	BigInt operator-() const;

	friend std::ostream& operator<<(std::ostream&, const BigInt&);

	friend BigInt& operator+(const BigInt&, const BigInt&);

	BigInt& operator+=(const BigInt&);

	BigInt operator++(int);

	BigInt& operator++();

	friend BigInt& operator-(BigInt&, BigInt&);

	BigInt& operator-=(const BigInt&);

	BigInt operator--(int);

	BigInt& operator--();

	friend BigInt& operator*(const BigInt&, const BigInt&);

	BigInt& operator*=(const BigInt&);

	friend BigInt& operator/(const BigInt&, BigInt&);

	BigInt& operator/=(BigInt&);

	friend bool operator==(const BigInt&, const BigInt&);

	friend bool operator!=(const BigInt&, const BigInt&);

	friend bool operator>=(const BigInt&, const BigInt&);

	friend bool operator<=(const BigInt&, const BigInt&);

	friend bool operator<(const BigInt&, const BigInt&);

	friend bool operator>(const BigInt&, const BigInt&);

	/*explicit operator int() const;*/

public:

	size_t length() const;

	static BigInt get_max_big_int();

	static BigInt get_min_big_int();


private:

	bool is_valid(const char*, size_t);

	void add(const BigInt&);

	void minus(const BigInt&);

	void mutiply(const BigInt&);

	void divide(BigInt&);

	static same_flag_t check_same(const BigInt&, const BigInt&, bool buffer_only = false);

	static void normalize(BigInt&, const BigInt&, const BigInt&);

	static void handle_carry(int, BigInt&);

	template<typename T>
	static void int2_buffer(T, BigInt&);

	static int char2int(char);

	static char int2char(int);

private:

	bool is_positive;

	buffer_t buffer;
};

#endif


