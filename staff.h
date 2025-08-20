#pragma once
#include "BST_Tree.h"
#include <iostream>
#include <cstdlib>

void staff()
{
	BST_Tree t;
	int condition = 0;

	while (condition != 5)
	{
		system("cls"); // Clear screen
		std::cout << "\n=== Staff Portal ===\n\n";
		std::cout << "1. View Transaction History\n";
		std::cout << "2. Transfer Money\n";
		std::cout << "3. Withdraw Money\n";
		std::cout << "4. Deposit Money\n";
		std::cout << "5. Exit\n\n";
		std::cout << "Enter your choice (1-5): ";
		std::cin >> condition;

		switch (condition)
		{
		case 1:
		{
			t.transaction_history();
			std::cout << "\nPress any key to return to menu...";
			system("pause > nul");
			break;
		}
		case 2:
		{
			int sender, receiver, amount;
			std::cout << "Enter sender's account number: ";
			std::cin >> sender;
			std::cout << "Enter receiver's account number: ";
			std::cin >> receiver;
			std::cout << "Enter amount to transfer: $";
			std::cin >> amount;

			t.transfer(sender, receiver, amount);
			std::cout << "\nPress any key to return to menu...";
			system("pause > nul");
			break;
		}
		case 3:
		{
			int account, amount;
			std::cout << "Enter account number: ";
			std::cin >> account;
			std::cout << "Enter amount to withdraw: $";
			std::cin >> amount;

			t.withdraw(account, amount);
			std::cout << "\nPress any key to return to menu...";
			system("pause > nul");
			break;
		}
		case 4:
		{
			int account, amount;
			std::cout << "Enter account number: ";
			std::cin >> account;
			std::cout << "Enter amount to deposit: $";
			std::cin >> amount;

			t.deposit(account, amount);
			std::cout << "\nPress any key to return to menu...";
			system("pause > nul");
			break;
		}
		case 5:
		{
			std::cout << "\nLogging out of Staff Portal...\n";
			break;
		}
		default:
		{
			std::cout << "\nInvalid choice! Please try again.\n";
			std::cout << "Press any key to continue...";
			system("pause > nul");
		}
		}
	}
}