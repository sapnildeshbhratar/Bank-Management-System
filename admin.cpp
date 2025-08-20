#include <iostream>
#include "admin.h"
#include "BST_Tree.h"
#include "Hashtable.h"
using namespace std;

void clearAdminScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void admin()
{
    BST_Tree t;
    Hashtable h;
    int condition = 0;

    while (condition != 6)
    {
        clearAdminScreen();
        cout << "\n     Welcome ADMIN\n";
        cout << "Choose one of the following options:\n";
        cout << "1. Add account\n";
        cout << "2. Delete account\n";
        cout << "3. Check all accounts\n";
        cout << "4. See password of account\n";
        cout << "5. Edit account (Not yet Implemented)\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> condition))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            system("pause");
            continue;
        }

        switch (condition)
        {
        case 1:
        {
            string name, email;
            long long acc;
            string password;
            double balance;

            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter email address: ";
            getline(cin, email);

            cout << "Enter account number: ";
            cin >> acc;

            cout << "Enter password: ";
            cin.ignore();
            getline(cin, password);

            cout << "Enter balance: ";
            cin >> balance;

            if (balance < 0)
            {
                cout << "\nError: Balance cannot be negative!\n";
                system("pause");
                continue;
            }

            t.add_Account(name, email, acc, password, balance);
            h.insert(acc, password);
            cout << "\nAccount created successfully!\n";
            system("pause");
            break;
        }
        case 2:
        {
            long long acc;
            cout << "Enter account number to delete: ";
            cin >> acc;
            t.load_Server();
            t.Root = t.delete_Account(t.Root, acc);
            h.delete_password(acc);
            t.update_server(t.Root);
            cout << "Account deleted successfully.\n";
            system("pause");
            break;
        }
        case 3:
        {
            t.load_Server();
            t.printoinfo(t.Root);
            system("pause");
            break;
        }
        case 4:
        {
            h.displayPasswords();
            system("pause");
            break;
        }
        case 5:
        {
            cout << "Edit account functionality not yet implemented.\n";
            system("pause");
            break;
        }
        case 6:
        {
            cout << "Exiting Admin menu.\n";
            break;
        }
        default:
        {
            cout << "Invalid option. Please try again.\n";
            system("pause");
        }
        }
    }
}
