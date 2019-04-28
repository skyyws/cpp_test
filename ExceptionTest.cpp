#include "ExceptionTest.h"
#include <string>
#include <iostream>
#include <exception>

void ExceptionTest::TestException() {
	try {
		std::string str;
		std::cout << str.c_str();
	} catch (std::exception e) {
		std::cout << "Exception" << std::endl;
	}
}