#include <iostream>
#include <cstdint>

#include "BigInt.h"


BigInt::BigInt()
	: is_positive(true), is_nan_(false) {

	buffer.fill(0);
}


// TODO::CHECK SIGN OF ZERO AND TURN TO POSITIVE;
BigInt::BigInt(const char* buffer, const size_t length)
	: BigInt() {

	if (is_valid(buffer, length)) {
		is_positive = buffer[0] != '-';

		const auto copy_length = is_positive ? length : length - 1;

		const buffer_t::pointer init_ptr = &this->buffer.front() + (kMaxLen - copy_length);

		memcpy(init_ptr, buffer + (is_positive ? 0 : 1), copy_length);
	}
}


BigInt::BigInt(int64_t num) : BigInt() {

	if (num < 0) {
		is_positive = false;
		num = abs(num);
	}

	int2_buffer(num, *this);
}


BigInt::BigInt(uint64_t num) : BigInt() {

	int2_buffer(num, *this);
}


BigInt::BigInt(int num) : BigInt() {

	if (num < 0) {
		is_positive = false;
		num = abs(num);
	}

	int2_buffer(num, *this);
}


BigInt BigInt::operator-() const {

	BigInt tmp(*this);
	tmp.is_positive = !this->is_positive;

	return tmp;
}


BigInt& operator+(const BigInt& lhs, const BigInt& rhs) {

	if (lhs.is_positive == rhs.is_positive) {

		auto num = lhs;

		num += rhs;

		return num;
	}
	if (lhs.is_positive) {
		auto num = lhs;

		num -= (-rhs);

		return num;
	}

	auto num = rhs;

	num -= (-lhs);

	return num;
}


BigInt BigInt::operator++(int) {

	auto tmp = *this;
	*this += BigInt("1", 1);

	return tmp;
}


BigInt& BigInt::operator++() {
	*this += BigInt("1", 1);
	return *this;
}


BigInt& BigInt::operator+=(const BigInt& rhs) {

	add(rhs);

	return *this;
}

BigInt& operator-(BigInt& lhs, BigInt& rhs) {

	return lhs + (-rhs);
}


BigInt& operator*(const BigInt& lhs, const BigInt& rhs) {

	auto num = BigInt(lhs);
	num *= rhs;

	return num;
}


BigInt& operator/(const BigInt& lhs, BigInt& rhs) {

	auto num = BigInt(lhs);
	num /= rhs;

	return num;
}


bool operator==(const BigInt& lhs, const BigInt& rhs) {

	return BigInt::check_same(lhs, rhs) == BigInt::kIsSame ? true : false;
}


bool operator!=(const BigInt& lhs, const BigInt& rhs) {

	return !(lhs == rhs);
}


bool operator>=(const BigInt& lhs, const BigInt& rhs) {

	return !(lhs < rhs);
}


bool operator<=(const BigInt& lhs, const BigInt& rhs) {

	return !(lhs > rhs);
}


bool operator<(const BigInt& lhs, const BigInt& rhs) {

	return BigInt::check_same(lhs, rhs) == BigInt::kRhsBigger ? true : false;
}


bool operator>(const BigInt& lhs, const BigInt& rhs) {

	return BigInt::check_same(lhs, rhs) == BigInt::kLhsBigger ? true : false;
}



BigInt& BigInt::operator-=(const BigInt& rhs) {

	minus(rhs);

	return *this;
}


BigInt BigInt::operator--(int) {

	auto tmp = *this;

	*this -= BigInt("1", 1);

	return tmp;
}


BigInt& BigInt::operator--() {
	*this -= BigInt("1", 1);
	return *this;
}


BigInt& BigInt::operator*=(const BigInt& rhs) {

	mutiply(rhs);

	return *this;
}

BigInt& BigInt::operator/=(BigInt& rhs) {
	try {
		divide(rhs);
	}
	catch (const std::runtime_error& e) {
		throw;
	}

	return *this;
}


void BigInt::add(const BigInt& rhs) {
	auto res = BigInt();

	int i = kMaxLen - 1;
	int j = kMaxLen - 1;
	const int* p_iter = this->length() > rhs.length() ? &i : &j;

	auto carry = false;

	while (i >= 0 || j >= 0) {
		int digit1 = (i >= 0) ? char2int(buffer[i]) : 0;
		int digit2 = (j >= 0) ? char2int(rhs.buffer[j]) : 0;

		auto value = digit1 + digit2 + carry;
		carry = value >= 10;

		res.buffer[*p_iter] = int2char(carry ? value % 10 : value);

		i--; j--;
	}

	res.is_positive = is_positive;

	*this = res;
}


void BigInt::minus(const BigInt& rhs) {

	BigInt res = BigInt();
	res.is_positive = check_same(*this, rhs, true) == kRhsBigger ? false : true;


	int carry = 0;
	int i = kMaxLen - 1;
	int j = kMaxLen - 1;
	const int* p_iter = this->length() > rhs.length() ? &i : &j;

	// 逐位相减
	while (i >= kMaxLen - this->length() || j >= kMaxLen - rhs.length()) {
		int digit1, digit2;
		if (res.is_positive) {
			digit1 = (i >= 0) ? char2int(buffer[i]) : 0;
			digit2 = (j >= 0) ? char2int(rhs.buffer[j]) : 0;

		}
		else {
			digit2 = (i >= 0) ? char2int(buffer[i]) : 0;
			digit1 = (j >= 0) ? char2int(rhs.buffer[j]) : 0;
		}

		// 处理借位
		if (carry) {
			digit1 -= 1;
			carry = 0;
		}

		// 判断是否需要借位
		if (digit1 < digit2) {
			digit1 += 10;
			carry = 1;
		}

		// 计算差值
		int diff = digit1 - digit2;
		res.buffer[*p_iter] = int2char(diff);

		i--; j--;
	}

	*this = res;
}


void BigInt::mutiply(const BigInt& rhs) {

	BigInt result;

	const auto lhs_len = length();
	const auto rhs_len = rhs.length();

	// 大整数乘法算法
	for (auto i = 0; i < lhs_len; ++i) {
		for (auto j = 0; j < rhs_len; ++j) {
			int product = char2int(buffer[kMaxLen - 1 - i]) *
				char2int(rhs.buffer[kMaxLen - 1 - j]);

			const int pos = kMaxLen - 1 - i - j;
			result.buffer[pos] += product;

			handle_carry(pos, result);
		}
	}
	BigInt::normalize(result, *this, rhs);

	*this = result;
}


void BigInt::divide(BigInt& rhs) {

	if (rhs.length() == 0) {
		is_nan_ = true;

		return;
	}

	BigInt quotient;
	BigInt remain;

	const auto lhs_len = length();
	auto remain_idx = kMaxLen - 1;

	while (remain_idx >= kMaxLen - lhs_len) {

		remain.buffer[remain_idx] = buffer[remain_idx];

		while (check_same(remain, rhs, true) != kRhsBigger) {
			remain -= rhs;
			quotient.buffer[kMaxLen - 1] += 1;
			for (int i = kMaxLen - 1; i >= kMaxLen - quotient.length(); --i) {
				handle_carry(i, quotient);
			}

		}
		--remain_idx;
	}
	normalize(quotient, *this, rhs);

	*this = quotient;
}


BigInt::same_flag_t BigInt::check_same(const BigInt& lhs, const BigInt& rhs, bool buffer_only) {

	if ((!buffer_only) && (lhs.is_positive != rhs.is_positive)) {

		return lhs.is_positive ? kLhsBigger : kRhsBigger;
	}
	if (lhs.buffer == rhs.buffer) {

		return kIsSame;
	}

	return lhs.buffer > rhs.buffer ? kLhsBigger : kRhsBigger;
}


void BigInt::normalize(BigInt& result, const BigInt& lhs, const BigInt& rhs) {

	for (auto i = kMaxLen - 1; i > kMaxLen - 1 - result.length(); --i) {
		result.buffer[i] = int2char(result.buffer[i]);
	}

	result.is_positive = !(lhs.is_positive ^ rhs.is_positive);
}


void BigInt::handle_carry(int current_index, BigInt& result) {
	while (result.buffer[current_index] > 9) {
		result.buffer[current_index] -= 10;

		++result.buffer[current_index - 1];
	}
}


template<typename T>
void BigInt::int2_buffer(T num, BigInt& big_int) {

	size_t i = kMaxLen - 1;

	while (num >= 1) {
		big_int.buffer[i] = int2char(num % 10);
		num /= 10;
		--i;
	}
}


int BigInt::char2int(char value) {

	return (value >= '0' && value <= '9') ? (value - '0') : 0;
}


char BigInt::int2char(int value) {

	return value + '0';
}


size_t BigInt::length() const {

	auto first = &buffer.front();
	auto count = 0;

	while (*first == 0 || *first == '0') {
		++first;
		++count;
	}

	return kMaxLen - count;
}


BigInt BigInt::get_max_big_int() {

	auto max = BigInt();

	max.buffer.fill('9');
	max.is_positive = true;

	return max;
}


BigInt BigInt::get_min_big_int() {

	auto min = BigInt::get_max_big_int();
	min.is_positive = false;

	return min;
}


bool BigInt::is_valid(const char* buffer, size_t length) {

	for (auto i = length - 1; i > 0; --i) {
		if (buffer[i] < 48 || buffer[i] > 57) {

			return false;
		}
	}
	if (buffer[0] == '+' ||
		buffer[0] == '-' ||
		(buffer[0] >= '0' && buffer[0] <= '9')) {

		return true;
	}

	return false;
}


std::ostream& operator<<(std::ostream& os, const BigInt& big_int) {

	if (big_int.is_nan_) {
		os << "NaN";
		return os;
	}

	big_int.is_positive || os << "-";

	for (auto i = BigInt::kMaxLen - big_int.length(); i < BigInt::kMaxLen; ++i) {
		os << big_int.buffer[i];
	}
	os << std::endl;

	return os;
}

