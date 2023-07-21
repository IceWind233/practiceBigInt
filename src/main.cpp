#include <iostream>
#include <vector>

/*
#include <gtest/gtest.h>
*/

#include "BigInt.h"
#include "MyVector.h"
#include "MyVector.cpp"
#include "SmartPtr.h"
#include "SmartPtr.cpp"


int main(int argc, char** argv) {

    std::unique_ptr<int> a = std::make_unique<int>(1);
    std::cout << *a.release();
    unique_ptr<int> aaa, b;

    aaa = make_unique<int>(1);
    b = make_unique<int>(2);
    aaa.swap(b);
    std::cout << aaa;


    return 0;
}
