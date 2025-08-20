#pragma once
#include "BST_Tree.h"
#include "Hashtable.h"
#include <iostream>

void customer()
{
	BST_Tree t;
	Hashtable h;
	int condition = 0;

	while (condition != 3)
	{
		system("cls"); // Clear screen for Windows
		std::cout << "\n===== Customer Portal =====\n\n";
		std::cout << "1. View Account Details\n";
		std::cout << "2. View Transaction History\n";
		std::cout << "3. Exit\n\n";
		std::cout << "Enter your choice (1-3): ";
		std::cin >> condition;

		switch (condition)
		{
		case 1:
		{
			long long accountno;
			std::cout << "\nEnter account number: ";
			std::cin >> accountno;

			BST_Node *temp = t.search(t.Root, accountno);
			if (temp != nullptr)
			{
				std::cout << "\n=== Account Details ===\n";
				std::cout << "Name: " << temp->name << "\n";
				std::cout << "Email: " << temp->email << "\n"; // Changed from adress to email
				std::cout << "Account Number: " << temp->account_number << "\n";
				std::cout << "Balance: $" << temp->balance << "\n";
			}
			else
			{
				std::cout << "\nAccount not found!\n";
			}
			break;
		}
		case 2:
			t.transaction_history();
			break;
		case 3:
			std::cout << "Thank you for using our services!" << std::endl;
			system("pause");
			break;
		default:
			std::cout << "Invalid choice! Please try again." << std::endl;
			system("pause");
			break;
		}

		if (condition != 3)
		{
			std::cout << "\nPress any key to continue...";
			system("pause > nul");
		}
	}
}