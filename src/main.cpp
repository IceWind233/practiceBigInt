#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include "BigInt.h"
#include "MyVector.h"
#include "MyVector.cpp"
#include "SmartPtr.h"
#include "SmartPtr.cpp"


TEST(UniquePtrTest, DefaultConstructor) {
	unique_ptr<int> ptr;
	EXPECT_FALSE(ptr);
	EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest, ConstructorWithRawPointer) {
	unique_ptr<int> ptr(new int(42));
	EXPECT_TRUE(ptr);
	EXPECT_EQ(*ptr, 42);
}

TEST(UniquePtrTest, MoveConstructor) {
	unique_ptr<int> ptr1(new int(42));
	unique_ptr<int> ptr2(std::move(ptr1));

	EXPECT_TRUE(ptr2);
	EXPECT_FALSE(ptr1);
	EXPECT_EQ(*ptr2, 42);
}

TEST(UniquePtrTest, MoveAssignmentOperator) {
	unique_ptr<int> ptr1(new int(42));
	unique_ptr<int> ptr2;

	ptr2 = std::move(ptr1);
	EXPECT_TRUE(ptr2);
	EXPECT_FALSE(ptr1);
	EXPECT_EQ(*ptr2, 42);
}

TEST(UniquePtrTest, Release) {
	unique_ptr<int> ptr(new int(42));
	int* rawPtr = ptr.release();

	EXPECT_TRUE(rawPtr);
	EXPECT_EQ(ptr.get(), nullptr);

	delete rawPtr;  // 可以手动删除资源
}

TEST(UniquePtrTest, Reset) {
	unique_ptr<int> ptr(new int(42));
	ptr.reset(nullptr);

	EXPECT_FALSE(ptr);
	EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest, ResetWithNewPointer) {
	unique_ptr<int> ptr(new int(42));
	ptr.reset(new int(24));

	EXPECT_TRUE(ptr);
	EXPECT_EQ(*ptr, 24);
}

TEST(SharedPtrTest, DefaultConstructor) {
	shared_ptr<int> ptr;
	EXPECT_FALSE(ptr);
	EXPECT_EQ(ptr.get(), nullptr);
}

TEST(SharedPtrTest, ConstructorWithRawPointer) {
	int* rawPtr = new int(42);
	shared_ptr<int> ptr(rawPtr);
	EXPECT_TRUE(ptr);
	EXPECT_EQ(*ptr, 42);
}

TEST(SharedPtrTest, CopyConstructor) {
	shared_ptr<int> ptr1(new int(42));
	shared_ptr<int> ptr2(ptr1);

	EXPECT_TRUE(ptr1);
	EXPECT_TRUE(ptr2);
	EXPECT_EQ(*ptr1, 42);
	EXPECT_EQ(*ptr2, 42);
}

TEST(SharedPtrTest, CopyAssignmentOperator) {
	shared_ptr<int> ptr1(new int(42));
	shared_ptr<int> ptr2;
	ptr2 = ptr1;

	EXPECT_TRUE(ptr1);
	EXPECT_TRUE(ptr2);
	EXPECT_EQ(*ptr1, 42);
	EXPECT_EQ(*ptr2, 42);
}

TEST(SharedPtrTest, MoveConstructor) {
	shared_ptr<int> ptr1(new int(42));
	shared_ptr<int> ptr2(std::move(ptr1));

	EXPECT_FALSE(ptr1);
	EXPECT_TRUE(ptr2);
	EXPECT_EQ(*ptr2, 42);
}

TEST(SharedPtrTest, MoveAssignmentOperator) {
	shared_ptr<int> ptr1(new int(42));
	shared_ptr<int> ptr2;

	ptr2 = std::move(ptr1);
	EXPECT_FALSE(ptr1);
	EXPECT_TRUE(ptr2);
	EXPECT_EQ(*ptr2, 42);
}

TEST(SharedPtrTest, Reset) {
	shared_ptr<int> ptr(new int(42));
	ptr.reset();

	EXPECT_FALSE(ptr);
	EXPECT_EQ(ptr.get(), nullptr);
}

TEST(SharedPtrTest, Swap) {
	shared_ptr<int> ptr1(new int(42));
	shared_ptr<int> ptr2(new int(24));

	ptr1.swap(ptr2);
	EXPECT_EQ(*ptr1, 24);
	EXPECT_EQ(*ptr2, 42);
}

TEST(SharedPtrTest, Get) {
	int* rawPtr = new int(42);
	shared_ptr<int> ptr(rawPtr);

	EXPECT_EQ(ptr.get(), rawPtr);
}

TEST(SharedPtrTest, UseCount) {
	shared_ptr<int> ptr1(new int(42));
	shared_ptr<int> ptr2(ptr1);
	shared_ptr<int> ptr3(ptr1);

	EXPECT_EQ(ptr1.use_count(), 3);
	EXPECT_EQ(ptr2.use_count(), 3);
	EXPECT_EQ(ptr3.use_count(), 3);
}

TEST(WeakPtrTest, ConstructorWithSharedPtr) {
	shared_ptr<int> sharedPtr(new int(42));
	weak_ptr<int> weakPtr(sharedPtr);

	EXPECT_EQ(weakPtr.use_count(), 1);
	EXPECT_FALSE(weakPtr.expired());
	EXPECT_EQ(*weakPtr.lock(), 42);
}

TEST(WeakPtrTest, CopyConstructor) {
	shared_ptr<int> sharedPtr(new int(42));
	weak_ptr<int> weakPtr1(sharedPtr);
	weak_ptr<int> weakPtr2(weakPtr1);

	EXPECT_EQ(weakPtr1.use_count(), 1);
	EXPECT_EQ(weakPtr2.use_count(), 1);
	EXPECT_EQ(*weakPtr2.lock(), 42);
}

TEST(WeakPtrTest, CopyAssignmentOperator) {
	shared_ptr<int> sharedPtr(new int(42));
	weak_ptr<int> weakPtr1(sharedPtr);
	weak_ptr<int> weakPtr2;
	weakPtr2 = weakPtr1;

	EXPECT_EQ(weakPtr1.use_count(), 1);
	EXPECT_EQ(weakPtr2.use_count(), 1);
	EXPECT_EQ(*weakPtr2.lock(), 42);
}

TEST(WeakPtrTest, MoveConstructor) {
	shared_ptr<int> sharedPtr(new int(42));
	weak_ptr<int> weakPtr1(sharedPtr);
	weak_ptr<int> weakPtr2(std::move(weakPtr1));

	EXPECT_EQ(weakPtr1.use_count(), 0);
	EXPECT_EQ(weakPtr2.use_count(), 1);
	EXPECT_EQ(*weakPtr2.lock(), 42);
}

TEST(WeakPtrTest, MoveAssignmentOperator) {
	shared_ptr<int> sharedPtr(new int(42));
	weak_ptr<int> weakPtr1(sharedPtr);
	weak_ptr<int> weakPtr2;
	weakPtr2 = std::move(weakPtr1);

	EXPECT_EQ(weakPtr1.use_count(), 0);
	EXPECT_EQ(weakPtr2.use_count(), 1);
	EXPECT_EQ(*weakPtr2.lock(), 42);
}

TEST(WeakPtrTest, Swap) {
	shared_ptr<int> sharedPtr1(new int(42));
	shared_ptr<int> sharedPtr2(new int(24));
	weak_ptr<int> weakPtr1(sharedPtr1);
	weak_ptr<int> weakPtr2(sharedPtr2);

	weakPtr1.swap(weakPtr2);
	EXPECT_EQ(weakPtr1.use_count(), 1);
	EXPECT_EQ(weakPtr2.use_count(), 1);
	EXPECT_EQ(*weakPtr1.lock(), 24);
	EXPECT_EQ(*weakPtr2.lock(), 42);
}

TEST(WeakPtrTest, UseCount) {
	shared_ptr<int> sharedPtr(new int(42));
	weak_ptr<int> weakPtr(sharedPtr);

	EXPECT_EQ(sharedPtr.use_count(), 1);
	EXPECT_EQ(weakPtr.use_count(), 1);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
