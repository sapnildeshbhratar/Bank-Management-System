#pragma once
#include "BST_Node.h"
#include "Hashtable.h"
#include <stdio.h>
class BST_Tree
{
	vector<int> v;

public:
	BST_Tree();
	Hashtable h;
	BST_Node *Root;
	void add_Account(std::string name, std::string email, long long acc, std::string password, double balance);
	BST_Node *delete_Account(BST_Node *, int);
	void withdraw(int, int);
	void deposit(int, int);
	void editaccount_byAdmin();
	void transfer(int, int, int);
	void transaction_history();
	void findMax(BST_Node *);
	void load_Server();
	void update_server(BST_Node *root); 
	BST_Node *search(BST_Node *, int);
	void printoinfo(BST_Node *);

private:
	void printInOrder(BST_Node *node);
};