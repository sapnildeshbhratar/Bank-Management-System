#pragma once
#include <string>

class Node_1
{
public:
	long long accountNumber;
	std::string password;
	Node_1 *next;

	Node_1();
	Node_1(long long acc, std::string pass);
};