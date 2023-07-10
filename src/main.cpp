#include <iostream>
#include <functional>
#include "BigInt.h"
#include <map>



int main(int argc, char* argv[]) {
	const char* ss1 = "123456";
	const char* ss2 = "3";
	BigInt big_int(ss1, strlen(ss1));
	BigInt big_int2(ss2, strlen(ss2));

	
	auto b = ( big_int );
	std::cout << b;

	return 0;
}
