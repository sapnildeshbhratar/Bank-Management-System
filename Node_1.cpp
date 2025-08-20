#include "Node_1.h"

Node_1::Node_1()
{
	accountNumber = 0;
	password = "";
	next = nullptr;
}

Node_1::Node_1(long long acc, std::string pass)
{
	accountNumber = acc;
	password = pass;
	next = nullptr;
}