#include <iostream>
#include "BigInt.h"
#include "gtest/gtest.h"


TEST(BigIntTest, DefaultConstructor) {
	BigInt bigInt;
	EXPECT_EQ(bigInt.length(), 0);
}

TEST(BigIntTest, ConstructorWithCharBuffer) {
	const char* buffer = "123456789";
	size_t length = strlen(buffer);
	BigInt bigInt(buffer, length);
	EXPECT_EQ(bigInt.length(), length);
	std::stringstream ss;
	ss << bigInt;
	EXPECT_EQ(ss.str(), "123456789\n");
}

TEST(BigIntTest, ConstructorWithNegativeCharBuffer) {
	const char* buffer = "-987654321";
	size_t length = strlen(buffer);
	BigInt bigInt(buffer, length);
	EXPECT_EQ(bigInt.length(), length - 1);
	std::stringstream ss;
	ss << bigInt;
	EXPECT_EQ(ss.str(), "-987654321\n");
}

TEST(BigIntTest, ConstructorWithPositiveInt64) {
	int64_t num = 9223372036854775807;
	BigInt bigInt(num);
	EXPECT_EQ(bigInt.length(), 19);
	std::stringstream ss;
	ss << bigInt;
	EXPECT_EQ(ss.str(), "9223372036854775807\n");
}

TEST(BigIntTest, ConstructorWithNegativeInt64) {
	int64_t num = -9223372036854775807;
	BigInt bigInt(num);
	EXPECT_EQ(bigInt.length(), 19);
	std::stringstream ss;
	ss << bigInt;
	EXPECT_EQ(ss.str(), "-9223372036854775807\n");
}

TEST(BigIntTest, ConstructorWithPositiveUInt64) {
	uint64_t num = 18446744073709551615U;
	BigInt bigInt(num);
	EXPECT_EQ(bigInt.length(), 20);
	std::stringstream ss;
	ss << bigInt;
	EXPECT_EQ(ss.str(), "18446744073709551615\n");
}

TEST(BigIntTest, ConstructorWithPositiveInt) {
	int num = 123456789;
	BigInt bigInt(num);
	EXPECT_EQ(bigInt.length(), 9);
	std::stringstream ss;
	ss << bigInt;
	EXPECT_EQ(ss.str(), "123456789\n");
}

TEST(BigIntTest, OperatorUnaryMinus) {
	BigInt bigInt("123456789", 9);
	BigInt result = -bigInt;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "-123456789\n");
}

TEST(BigIntTest, OperatorPlus) {
	BigInt lhs("12345", 5);
	BigInt rhs("67890", 5);
	BigInt result = lhs + rhs;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "80235\n");
}

TEST(BigIntTest, OperatorIncrementPostfix) {
	BigInt bigInt("12345", 5);
	BigInt result = bigInt++;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "12345\n");
	ss.str("");
	ss << bigInt;
	EXPECT_EQ(ss.str(), "12346\n");
}

TEST(BigIntTest, OperatorIncrementPrefix) {
	BigInt bigInt("12345", 5);
	BigInt result = ++bigInt;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "12346\n");
	ss.str("");
	ss << bigInt;
	EXPECT_EQ(ss.str(), "12346\n");
}

TEST(BigIntTest, OperatorPlusEqual) {
	BigInt lhs("12345", 5);
	BigInt rhs("67890", 5);
	lhs += rhs;
	std::stringstream ss;
	ss << lhs;
	EXPECT_EQ(ss.str(), "80235\n");
}

TEST(BigIntTest, OperatorMinus) {
	BigInt lhs("123456789", 9);
	BigInt rhs("987654321", 9);
	BigInt result = lhs - rhs;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "-864197532\n");
}

TEST(BigIntTest, OperatorDecrementPostfix) {
	BigInt bigInt("12345", 5);
	BigInt result = bigInt--;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "12345\n");
	ss.str("");
	ss << bigInt;
	EXPECT_EQ(ss.str(), "12344\n");
}


TEST(BigIntTest, OperatorMinusEqual) {
	BigInt lhs("-123456789", 10);
	BigInt rhs("-987654321", 10);
	lhs -= rhs;
	std::stringstream ss;
	ss << lhs;
	EXPECT_EQ(ss.str(), "-864197532\n");
}

TEST(BigIntTest, OperatorMultiply) {
	BigInt lhs("12345", 5);
	BigInt rhs("67890", 5);
	BigInt result = lhs * rhs;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "838102050\n");
}

TEST(BigIntTest, OperatorMultiplyEqual) {
	BigInt lhs("12345", 5);
	BigInt rhs("67890", 5);
	lhs *= rhs;
	std::stringstream ss;
	ss << lhs;
	EXPECT_EQ(ss.str(), "838102050\n");
}

TEST(BigIntTest, OperatorDivide) {
	BigInt lhs("1234567890", 10);
	BigInt rhs("12345", 5);
	BigInt result = lhs / rhs;
	std::stringstream ss;
	ss << result;
	EXPECT_EQ(ss.str(), "100005\n");
}

TEST(BigIntTest, OperatorDivideByZero) {
	BigInt lhs("1234567890", 10);
	BigInt rhs;
	ASSERT_THROW(lhs / rhs, std::runtime_error);
}

TEST(BigIntTest, OperatorDivideEqual) {
	BigInt lhs("1234567890", 10);
	BigInt rhs("12345", 5);
	lhs /= rhs;
	std::stringstream ss;
	ss << lhs;
	EXPECT_EQ(ss.str(), "100005\n");
}


TEST(BigIntTest, OperatorEquality) {
	BigInt lhs("123456789", 9);
	BigInt rhs("123456789", 9);
	EXPECT_EQ(lhs == rhs, true);
}

TEST(BigIntTest, OperatorInequality) {
	BigInt lhs("123456789", 9);
	BigInt rhs("987654321", 9);
	EXPECT_EQ(lhs != rhs, true);
}

TEST(BigIntTest, OperatorLessThan) {
	BigInt lhs("12345", 5);
	BigInt rhs("67890", 5);
	EXPECT_EQ(lhs < rhs, true);
}

TEST(BigIntTest, OperatorLessThanOrEqual) {
	BigInt lhs("12345", 5);
	BigInt rhs("12345", 5);
	EXPECT_EQ(lhs <= rhs, true);
}

TEST(BigIntTest, OperatorGreaterThan) {
	BigInt lhs("67890", 5);
	BigInt rhs("12345", 5);
	EXPECT_EQ(lhs > rhs, true);
}

TEST(BigIntTest, OperatorGreaterThanOrEqual) {
	BigInt lhs("12345", 5);
	BigInt rhs("12345", 5);
	EXPECT_EQ(lhs >= rhs, true);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}