#include "CppTest.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

void CppTest::ReadFile() {
	string path = "/Users/wangs/project/c/test";
	ifstream path_input(path, ios::in);

	stringstream ss;
	ss << path_input.rdbuf();
	cout << "----" << ss.str();
}

void CppTest::RemoveFile() {
	string path = "/Users/wangs/project/c/test";
	int ret = remove(path.c_str());
	std::cout << ret;
}

void CppTest::StrCompare() {
	string str = "add";
	std::cout << str.compare("adda") << std::endl;
}

void CppTest::StringToNumber() {
	string str = "12345A";
	long num = atol(str.c_str());
	std::cout << num << std::endl;
}

void CppTest::SleepTest() {
    cout << "Start----" << endl;
    sleep(5);
    cout << "End----" << endl;
}
