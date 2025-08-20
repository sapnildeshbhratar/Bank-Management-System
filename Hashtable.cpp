#include "Hashtable.h"
#include <iostream>
#include <fstream>
#include <vector>

void Hashtable::starthash()
{
	for (int i = 0; i < tableSize; i++)
	{
		Node *temp1 = new Node(i);
		if (start == nullptr)
		{
			start = temp1;
		}
		else
		{
			Node *current = start;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = temp1;
		}
	}
	loadhashtable(); 
}
void Hashtable::add(int a, int p)
{
	static int i = 0;
	ofstream write;
	write.open("hashtable.txt", ios::app);
	if (i != 0)
	{
		write << endl;
		write << a << endl
			  << p;
	}
	else
	{
		i++;
		write << a << endl
			  << p;
	}
	write.close();

	starthash();
}
bool Hashtable::match(int a, std::string p) // Changed password parameter to string
{
	bool flag = false;
	int r = a % 10;
	Node *c = start;
	while (c->data != r)
	{
		c = c->next;
	}
	Node_1 *c1 = c->pre;
	while (c1 != nullptr)
	{
		if (c1->accountNumber == a && c1->password == p)
		{
			flag = true;
			break;
		}
		c1 = c1->next;
	}
	return flag;
}
void Hashtable::display()
{
	Node *current = start;
	while (current != nullptr)
	{
		cout << current->data << endl;
		current = current->next;
	}
}
void Hashtable::loadhashtable()
{
	long long acc;
	std::string pass;

	std::ifstream read("hashtable.txt");
	if (!read.is_open())
	{
		std::cout << "Error: Unable to open hashtable.txt\n";
		return;
	}

	while (read >> acc >> pass)
	{
		int index = acc % tableSize;
		Node_1 *newNode = new Node_1(acc, pass);

		if (arr[index] == nullptr)
		{
			arr[index] = newNode;
		}
		else
		{
			Node_1 *temp = arr[index];
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}

		Node *current = start;
		while (current != nullptr && current->data != (acc % 10))
		{
			current = current->next;
		}
		if (current != nullptr)
		{
			newNode->next = current->pre;
			current->pre = newNode;
		}
	}
	read.close();
}
void Hashtable::displayPasswords()
{
	starthash();
	if (start == nullptr)
	{
		std::cout << "No accounts found.\n";
		return;
	}

	std::cout << "\n=== All Account Details ===\n\n";
	Node *c = start;
	while (c != nullptr)
	{
		Node_1 *c1 = c->pre;
		while (c1 != nullptr)
		{
			std::cout << "Account Number: " << c1->accountNumber << "\n";
			std::cout << "Password: " << c1->password << "\n";
			std::cout << "------------------------\n";
			c1 = c1->next;
		}
		c = c->next;
	}
	std::cout << "\nEnd of account list.\n";
}
void Hashtable::delete_password(int accountno)
{
	ifstream read;
	read.open("hashtable.txt");
	vector<int> v;
	int acc = 0, pass = 0;
	int i = 0;
	while (!read.eof())
	{
		i++;
		read >> acc;
		read >> pass;
		if (acc == accountno)
		{ // read both account number and password to skip them
			continue;
		}
		v.push_back(acc);
		v.push_back(pass);
	}
	read.close();
	ofstream write;
	write.open("temp.txt", ios::app);

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] != 0)
		{
			write << v[i] << endl;
		}
	}

	write.close();
	remove("hashtable.txt");
	rename("temp.txt", "hashtable.txt");
}
void Hashtable::insert(long long acc, std::string password)
{
	int index = acc % tableSize;

	Node_1 *newNode = new Node_1(acc, password);

	if (arr[index] == nullptr)
	{
		arr[index] = newNode;
	}
	else
	{
		Node_1 *temp = arr[index];
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}

	std::ofstream outFile("hashtable.txt", std::ios::app);
	if (outFile.is_open())
	{
		outFile << acc << " " << password << std::endl;
		outFile.close();
	}
}