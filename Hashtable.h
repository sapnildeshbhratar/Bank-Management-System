#pragma once
#include "Node.h"
#include "Node_1.h"
#include <string>

class Hashtable
{
private:
	static const int tableSize = 100;
	Node *start;
	Node_1 *arr[tableSize];

public:
	Hashtable()
	{
		start = nullptr;
		for (int i = 0; i < tableSize; i++)
		{
			arr[i] = nullptr;
		}
	}

	void starthash();
	void add(int a, int p);
	bool match(int a, std::string p); 
	void display();
	void loadhashtable(); 
	void displayPasswords();
	void delete_password(int accountno);
	void insert(long long acc, std::string password);
};