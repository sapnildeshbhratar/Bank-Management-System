#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <string>
class BST_Node
{
public:
	string name;
	string email;
	long long account_number;
	string password;
	double balance;
	BST_Node *left;
	BST_Node *right;

	BST_Node();
	BST_Node(string n, string e, long long acc, string pass, double bal);
};