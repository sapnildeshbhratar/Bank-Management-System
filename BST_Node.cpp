#include "BST_Node.h"

BST_Node::BST_Node()
{
	name = "";
	email = "";
	account_number = 0;
	password = "";
	balance = 0.0;
	left = nullptr;
	right = nullptr;
}

BST_Node::BST_Node(string n, string e, long long acc, string pass, double bal)
{
	name = n;
	email = e;
	account_number = acc;
	password = pass;
	balance = bal;
	left = nullptr;
	right = nullptr;
}
