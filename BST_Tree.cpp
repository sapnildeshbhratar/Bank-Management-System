#include <stack>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "BST_Tree.h"
#include "Hashtable.h"
BST_Tree::BST_Tree()
{
}
void BST_Tree::add_Account(string name, string email, long long acc, string password, double balance)
{
	if (Root == nullptr)
	{
		Root = new BST_Node(name, email, acc, password, balance);
	}
	else
	{
		BST_Node *current = Root;
		BST_Node *parent = nullptr;

		while (current != nullptr)
		{
			parent = current;
			if (acc < current->account_number)
			{
				current = current->left;
			}
			else if (acc > current->account_number)
			{
				current = current->right;
			}
			else
			{
				cout << "\nAccount number already exists!\n";
				return;
			}
		}

		BST_Node *newNode = new BST_Node(name, email, acc, password, balance);
		if (acc < parent->account_number)
		{
			parent->left = newNode;
		}
		else
		{
			parent->right = newNode;
		}
	}
	update_server(Root);
}

BST_Node *BST_Tree::delete_Account(BST_Node *root, int accountno)
{
	

	// cout << "accountno"<<root->account_number;
	if (root == nullptr)
		cout << "it seems that Tree is empty OR You have entered wrong data" << endl;
	else if (accountno < root->account_number)
		root->left = delete_Account(root->left, accountno);
	else if (accountno > Root->account_number)
		root->right = delete_Account(root->right, accountno);
	else
	{
		if (root->left && root->right)
		{
			findMax(root->left);
			root->account_number = v.back();
			root->left = delete_Account(root->left, root->account_number);
		}
		else
		{
			cout << "aya" << endl;
			BST_Node *temp = root;
			if (root->left == nullptr)
				root = root->right;
			else if (root->right == nullptr)
				root = root->left;
			delete temp;
		}
	}
	return (root);
}
void BST_Tree::withdraw(int accountno, int amount)
{
	load_Server();
	BST_Node *temp = search(Root, accountno);
	temp->balance = temp->balance - amount;
	vector<int> data;
	ifstream read;
	read.open("transaction.txt", ios::app);
	int line = 0;
	while (!read.eof())
	{
		read >> line;
		if (line == accountno)
		{
			data.push_back(line);
			line = (amount * -1);
			data.push_back(line);
			continue;
		}
		data.push_back(line);
	}
	read.close();

	ofstream write;
	write.open("temp.txt", ios::app);
	for (int i = 0; i < data.size(); i++)
	{
		write << data[i] << endl;
	}
	write.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");

	update_server(Root);
}
void BST_Tree::deposit(int accountno, int amount)
{
	load_Server();
	BST_Node *temp = search(Root, accountno);
	temp->balance = temp->balance + amount;

	vector<int> data;
	ifstream read;
	read.open("transaction.txt", ios::app);
	int line = 0;
	while (!read.eof())
	{
		read >> line;
		if (line == accountno)
		{
			data.push_back(line);
			line = amount;
			data.push_back(line);
			continue;
		}
		data.push_back(line);
	}
	read.close();

	ofstream write;
	write.open("temp.txt", ios::app);
	for (int i = 0; i < data.size(); i++)
	{
		write << data[i] << endl;
	}
	write.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");

	update_server(Root);
}
void BST_Tree::editaccount_byAdmin()
{
}
void BST_Tree::transfer(int sender_accountno, int reciever_accountno, int sender_amount)
{

	// happening in tree
	BST_Node *sender = search(Root, sender_accountno);
	sender->balance = sender->balance - sender_amount;
	BST_Node *reciever = search(Root, reciever_accountno);
	reciever->balance = reciever->balance + sender_amount;
	update_server(Root);

	// Now happening in the transacton file

	//  for sender
	vector<int> data;
	ifstream read;
	read.open("transaction.txt", ios::app);
	int line = 0;
	while (!read.eof())
	{
		read >> line;
		if (line == sender_accountno)
		{
			data.push_back(line);
			line = (sender_amount * -1);
			data.push_back(line);
			continue;
		}
		data.push_back(line);
	}
	read.close();

	ofstream write;
	write.open("temp.txt", ios::app);
	for (int i = 0; i < data.size(); i++)
	{
		write << data[i] << endl;
	}
	write.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");

	//  for reciever

	while (!read.eof())
	{
		read >> line;
		if (line == reciever_accountno)
		{
			data.push_back(line);
			line = sender_amount;
			data.push_back(line);
			continue;
		}
		data.push_back(line);
	}
	read.close();

	write.open("temp.txt", ios::app);
	for (int i = 0; i < data.size(); i++)
	{
		write << data[i] << endl;
	}
	write.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");
}
void BST_Tree::transaction_history()
{
	ifstream read;
	read.open("transaction.txt");
	string line;
	while (getline(read, line))
	{
		cout << line << endl;
	}
	read.close();
}
void BST_Tree::findMax(BST_Node *root)
{
	if (root)
	{
		findMax(root->left);
		v.push_back(root->account_number);
		findMax(root->right);
	}
}
void BST_Tree::load_Server()
{
	// Clear existing tree
	Root = nullptr;

	std::ifstream read("server.txt");
	if (!read.is_open())
	{
		std::cout << "Error: Unable to open server.txt\n";
		return;
	}

	std::string name, email, password;
	long long account_number;
	double balance;

	// Read line by line to handle spaces in strings
	while (!read.eof())
	{
		std::getline(read, name);
		if (name.empty())
			continue; // Skip empty lines

		std::getline(read, email);
		read >> account_number;
		read.ignore(); // Clear newline
		std::getline(read, password);
		read >> balance;
		read.ignore(); // Clear newline

		if (Root == nullptr)
		{
			Root = new BST_Node(name, email, account_number, password, balance);
		}
		else
		{
			add_Account(name, email, account_number, password, balance);
		}
	}
	read.close();
}

void BST_Tree::printoinfo(BST_Node *root)
{
	// First load the current data
	load_Server();

	if (Root == nullptr)
	{
		std::cout << "No accounts found in the system.\n";
		std::cout << "Please add some accounts first.\n";
		return;
	}

	std::cout << "\n=== All Account Details ===\n\n";
	printInOrder(Root);
	std::cout << "\nEnd of account list.\n";
}

void BST_Tree::printInOrder(BST_Node *node)
{
	if (node == nullptr)
		return;

	printInOrder(node->left);

	std::cout << "Account Details:\n";
	std::cout << "-----------------\n";
	std::cout << "Name: " << node->name << "\n";
	std::cout << "Email: " << node->email << "\n";
	std::cout << "Account Number: " << node->account_number << "\n";
	std::cout << "Balance: $" << std::fixed << std::setprecision(2) << node->balance << "\n";
	std::cout << "-----------------\n\n";

	printInOrder(node->right);
}
BST_Node *BST_Tree::search(BST_Node *root, int accountno)
{
	// Base cases: root is null or account number is at root
	if (root == nullptr || root->account_number == accountno)
		return root;

	// Account number is greater than root's account number
	if (accountno > root->account_number)
		return search(root->right, accountno);

	// Account number is smaller than root's account number
	return search(root->left, accountno);
}
void BST_Tree::update_server(BST_Node *root)
{
	if (root == nullptr)
		return;

	// Clear file contents first when starting with Root
	if (root == Root)
	{
		std::ofstream clear("server.txt", std::ios::trunc);
		clear.close();
	}

	// Now append in-order traversal to file
	std::ofstream write("server.txt", std::ios::app);
	if (write.is_open())
	{
		write << root->name << std::endl;
		write << root->email << std::endl;
		write << root->account_number << std::endl;
		write << root->password << std::endl;
		write << root->balance << std::endl;

		// Recursively update left and right subtrees
		update_server(root->left);
		update_server(root->right);

		write.close();
	}
}
