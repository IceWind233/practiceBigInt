#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include "BigInt.h"
#include "MyVector.h"
#include "MyVector.cpp"


TEST(VectorTest, DefaultConstructor) {
    vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, SizeConstructor) {
    vector<int> vec(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_GE(vec.capacity(), 5);
    EXPECT_FALSE(vec.empty());
}

TEST(VectorTest, ValueConstructor) {
    vector<int> vec(3, 10);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_GE(vec.capacity(), 3);
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 10);
    }
}

TEST(VectorTest, IteratorConstructor) {
    vector<int> values = { 1, 2, 3, 4, 5 };
    auto begin = values.begin();
    auto end = values.end();

    vector<int> vec(begin, end);
    EXPECT_EQ(vec.size(), values.size());
    EXPECT_GE(vec.capacity(), values.size());
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], values[i]);
    }
}

TEST(VectorTest, InitializerListConstructor) {
    vector<int> vec = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(vec.size(), 5);
    EXPECT_GE(vec.capacity(), 5);
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], i + 1);
    }
}

TEST(VectorTest, CopyConstructor) {
    vector<int> vec1 = { 1, 2, 3 };
    vector<int> vec2(vec1);

    EXPECT_EQ(vec2.size(), vec1.size());
    EXPECT_GE(vec2.capacity(), vec1.size());
    EXPECT_FALSE(vec2.empty());

    for (int i = 0; i < vec2.size(); ++i) {
        EXPECT_EQ(vec2[i], vec1[i]);
    }
}

TEST(VectorTest, MoveConstructor) {
    vector<int> vec1 = { 1, 2, 3 };
    vector<int> vec2(std::move(vec1));

    EXPECT_EQ(vec2.size(), 3);
    EXPECT_GE(vec2.capacity(), 3);
    EXPECT_FALSE(vec2.empty());

    for (int i = 0; i < vec2.size(); ++i) {
        EXPECT_EQ(vec2[i], i + 1);
    }
}

TEST(VectorTest, CopyAssignmentOperator) {
    vector<int> vec1 = { 1, 2, 3 };
    vector<int> vec2;
    vec2 = vec1;

    EXPECT_EQ(vec2.size(), vec1.size());
    EXPECT_GE(vec2.capacity(), vec1.size());
    EXPECT_FALSE(vec2.empty());

    for (int i = 0; i < vec2.size(); ++i) {
        EXPECT_EQ(vec2[i], vec1[i]);
    }
}

TEST(VectorTest, MoveAssignmentOperator) {
    vector<int> vec1 = { 1, 2, 3 };
    vector<int> vec2;
    vec2 = std::move(vec1);

    EXPECT_EQ(vec2.size(), 3);
    EXPECT_GE(vec2.capacity(), 3);
    EXPECT_FALSE(vec2.empty());

    for (int i = 0; i < vec2.size(); ++i) {
        EXPECT_EQ(vec2[i], i + 1);
    }
}

TEST(VectorTest, IndexOperator) {
    vector<int> vec = { 1, 2, 3 };

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], i + 1);
    }

    vec[1] = 10;
    EXPECT_EQ(vec[1], 10);
}

TEST(VectorTest, FrontAndBackFunctions) {
    vector<int> vec = { 1, 2, 3 };

    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 3);

    vec.front() = 10;
    vec.back() = 30;

    EXPECT_EQ(vec.front(), 10);
    EXPECT_EQ(vec.back(), 30);
}

TEST(VectorTest, PushBackFunction) {
    vector<int> vec;

    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
        EXPECT_EQ(vec.size(), i);
        EXPECT_GE(vec.capacity(), i);
        EXPECT_FALSE(vec.empty());
        EXPECT_EQ(vec.back(), i);
    }
}

TEST(VectorTest, PopBackFunction) {
    vector<int> vec = { 1, 2, 3 };

    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_GE(vec.capacity(), 4);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.back(), 2);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GE(vec.capacity(), 4);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.back(), 1);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, ReserveFunction) {
    vector<int> vec;

    vec.reserve(10);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_GE(vec.capacity(), 10);
    EXPECT_TRUE(vec.empty());

    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
    }

    vec.reserve(20);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_GE(vec.capacity(), 20);
    EXPECT_FALSE(vec.empty());

    for (int i = 1; i <= 5; ++i) {
        EXPECT_EQ(vec[i - 1], i);
    }
}

TEST(VectorTest, ResizeFunction) {
    vector<int> vec;

    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_GE(vec.capacity(), 5);
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 0);
    }

    vec.resize(3);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_GE(vec.capacity(), 3);
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 0);
    }
}

TEST(VectorTest, ClearFunction) {
    vector<int> vec = { 1, 2, 3 };

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, SwapFunction) {
    vector<int> vec1 = { 1, 2, 3 };
    vector<int> vec2 = { 4, 5 };

    vec1.swap(vec2);

    EXPECT_EQ(vec1.size(), 2);
    EXPECT_EQ(vec1[0], 4);
    EXPECT_EQ(vec1[1], 5);

    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, AssignInitializerList) {
    vector<int> vec;

    vec.assign({ 1, 2, 3 });
    EXPECT_EQ(vec.size(), 3);
    EXPECT_GE(vec.capacity(), 3);
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], i + 1);
    }
}

TEST(VectorTest, AssignIteratorRange) {
    vector<int> values = { 1, 2, 3, 4, 5 };
    vector<int>::iterator begin = values.begin();
    vector<int>::iterator end = values.end();

    vector<int> vec;
    vec.assign(begin, end);

    EXPECT_EQ(vec.size(), values.size());
    EXPECT_GE(vec.capacity(), values.size());
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], values[i]);
    }
}

TEST(VectorTest, BeginAndEndFunctions) {
    vector<int> vec = { 1, 2, 3 };

    int count = 1;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        EXPECT_EQ(*it, count++);
    }
}

TEST(VectorTest, EraseFunction) {
    vector<int> vec = { 1, 2, 3, 4, 5 };

    auto it = vec.erase(vec.begin() + 2);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_GE(vec.capacity(), 8);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 4);

    it = vec.erase(vec.begin(), vec.begin() + 2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_GE(vec.capacity(), 8);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 4);
}

TEST(VectorTest, InsertValue) {
    vector<int> vec = { 1, 2, 5 };

    auto it = vec.insert(vec.begin() + 2, 3);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_GE(vec.capacity(), 4);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 3);

    it = vec.insert(vec.begin(), 0);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_GE(vec.capacity(), 5);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 0);
}

TEST(VectorTest, InsertCountAndValue) {
    vector<int> vec = { 1, 2, 5 };

    auto it = vec.insert(vec.begin() + 2, 3, 4);
    EXPECT_EQ(vec.size(), 6);
    EXPECT_GE(vec.capacity(), 8);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 4);

    it = vec.insert(vec.begin(), 2, 0);
    EXPECT_EQ(vec.size(), 8);
    EXPECT_GE(vec.capacity(), 16);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 0);
}

TEST(VectorTest, InsertIteratorRange) {
    vector<int> vec = { 1, 2, 5 };
    vector<int> values = { 3, 4 };

    auto it = vec.insert(vec.begin() + 2, values.begin(), values.end());
 
    EXPECT_GE(vec.capacity(), 5);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 3);

    it = vec.insert(vec.begin(), values.begin(), values.end());
    EXPECT_EQ(vec.size(), 7);
    EXPECT_GE(vec.capacity(), 7);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, 3);
}

TEST(VectorTest, EmplaceFunction) {
    vector<std::string> vec = { "Hello", "World" };

    auto it = vec.emplace(vec.begin() + 1, "Beautiful");
    EXPECT_EQ(vec.size(), 3);
    EXPECT_GE(vec.capacity(), 3);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, "Beautiful");

    it = vec.emplace(vec.begin(), "Hi");
    EXPECT_EQ(vec.size(), 4);
    EXPECT_GE(vec.capacity(), 4);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(*it, "Hi");
}

TEST(VectorTest, EmplaceBackFunction) {
    vector<std::string> vec;
    vec.emplace_back("Hello");
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GE(vec.capacity(), 1);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.back(), "Hello");
    vec.emplace_back("World");
    EXPECT_EQ(vec.size(), 2);
    EXPECT_GE(vec.capacity(), 2);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.back(), "World");
}


int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
