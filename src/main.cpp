#include <iostream>

#include "BigInt.h"
#include "MyVector.h"
#include "MyVector.cpp"



int main(int argc, char* argv[]) {

	auto a = vector<int>({ 1, 2, 3 });
	auto b = vector<int>({3, 4, 5, 6, 7, 8, 9});

	b = std::move(a);

	std::cout << b;
	
	return 0;
}


