#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Hashtable.h"
#include "BST_Tree.h"
#include "admin.h"
#include "staff.h"
#include "customer.h"

class BankSystem
{
private:
	Hashtable hashTable;
	BST_Tree bstTree;

	void clearScreen()
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");

#endif
	}

	bool checkFiles()
	{
		try
		{
			const char *files[] = {"server.txt", "transaction.txt", "hashtable.txt"};
			for (const char *file : files)
			{
				std::ofstream outFile(file, std::ios::app);
				if (!outFile)
				{
					throw std::runtime_error(std::string("Cannot open file: ") + file);
				}
				outFile.close();
			}
			return true;
		}
		catch (const std::exception &e)
		{
			std::cerr << "File error: " << e.what() << std::endl;
			return false;
		}
	}

	void displayMenu()
	{
		clearScreen();
		std::cout << "\n===== Bank Management System =====\n\n"
				  << "1. ADMIN Login\n"
				  << "2. STAFF Login\n"
				  << "3. CUSTOMER Login\n"
				  << "4. EXIT\n\n"
				  << "Please enter your choice (1-4): ";
	}

public:
	bool initialize()
	{
		std::cout << "Bank Management System Starting..." << std::endl;

		if (!checkFiles())
		{
			return false;
		}

		try
		{
			hashTable.starthash();
			bstTree.load_Server();
			return true;
		}
		catch (const std::exception &e)
		{
			std::cerr << "Initialization error: " << e.what() << std::endl;
			return false;
		}
	}

	void run()
	{
		int choice = 0;
		while (choice != 4)
		{
			displayMenu();

			if (!(std::cin >> choice))
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "\nInvalid input. Please enter a number.\n";
				system("pause");
				continue;
			}

			try
			{
				switch (choice)
				{
				case 1:
					admin();
					break;
				case 2:
					staff();
					break;
				case 3:
					customer();
					break;
				case 4:
					std::cout << "\nThank you for using Bank Management System!\n";
					break;
				default:
					std::cout << "\nInvalid choice. Please try again.\n";
					system("pause");
				}
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
				system("pause");
			}
		}
	}
};

int main()
{
	BankSystem bank;
	if (!bank.initialize())
	{
		std::cerr << "Failed to initialize bank system.\n";
		system("pause");
		return 1;
	}

	bank.run();
	system("pause");
	return 0;
}