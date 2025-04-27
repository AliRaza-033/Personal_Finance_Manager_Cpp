/*
-------------------------------------------------------------------------------------
Author :- Ali Raza
Created at:- 15-Dec-2024
Project:- Personal finance management
-------------------------------------------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

void registerUser();
bool loginUser();
void addRecord();
void viewRecords();
void deleteRecord();
void calculateSummary();
void mainMenu();
void validations();
void financialAdvisor();
void clearScreen()
{
    system("cls");
}

struct Record
{
    string date;
    string category;
    string username;
    double amount;
    char type;
};

string currentUser;

int main()
{
    int userChoice;

    cout << "========================================================================\n";
    cout << "||                   Welcome to Personal Finance Tracker              ||\n";
    cout << "========================================================================\n";
    do
    {
        cout << "\nPlease select an option:\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "| 1. Register              |\n";
        cout << "----------------------------\n";
        cout << "| 2. Login                 |\n";
        cout << "----------------------------\n";
        cout << "| 3. Exit                  |\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice (1-3): ";

        cin >> userChoice;

        if (cin.fail() || userChoice < 1 || userChoice > 3)
        {
            cout << "\n[Error] Invalid input! Please enter a number between 1 and 3.\n";
            validations();
            continue;
        }

        validations();
        if (userChoice == 1)
        {
            registerUser();
            if (loginUser())
            {
                mainMenu();
            }
        }
        else if (userChoice == 2 && loginUser())
        {
            mainMenu();
        }

    } while (userChoice != 3);
    clearScreen();
    cout << "Exiting program....\n";
    cout << "\nThank you for using Personal Finance Tracker!\n\n";
    return 0;
}

void registerUser()
{
    ofstream userFile("D:\\PF LAb project Practices\\Group_no_1\\user.txt", ios::app);
    string username, password, existingUsername, existingPassword;
    clearScreen();
    cout << "\n---------------------------\n";
    cout << "---- Register New User ----\n";
    cout << "---------------------------\n";

    while (true)
    {
        cout << "\nEnter a new username: ";
        getline(cin, username);

        ifstream userFileRead("D:\\PF LAb project Practices\\Group_no_1\\user.txt");
        bool usernameExists = false;

        while (userFileRead >> existingUsername >> existingPassword)
        {
            if (existingUsername == username)
            {
                cout << "\n[Error] Username already exists! Please try again.\n";
                usernameExists = true;
                break;
            }
        }

        userFileRead.close();

        if (!usernameExists)
        {
            break;
        }
    }

    cout << "Enter a new password: ";
    getline(cin, password);

    userFile << username << " " << password << "\n";
    userFile.close();
    cout << "\n[Success] Registration successful! You can now log in.\n";
    cout << "\n============================================================\n";
}
bool loginUser()
{
    ifstream userFile("D:\\PF LAb project Practices\\Group_no_1\\user.txt");
    string username, password, inputUsername, inputPassword;

    cout << "\n---------------------------";
    cout << "\n ----   User Login   ---- \n";
    cout << "---------------------------\n";

    cout << "Enter username: ";
    getline(cin, inputUsername);

    cout << "Enter password: ";
    getline(cin, inputPassword);

    while (userFile >> username >> password)
    {
        if (username == inputUsername && password == inputPassword)
        {
            clearScreen();
            cout << "\n[Success] Login successful! Welcome, " << inputUsername << "!\n";
            currentUser = inputUsername;
            userFile.close();
            return true;
        }
    }

    cout << "\n[Error] Invalid credentials! Please try again.\n";
    userFile.close();
    return false;
}

void addRecord()
{
    ofstream recordsFile("D:\\PF LAb project Practices\\Group_no_1\\records.txt", ios::app);
    Record newRecord;

    cout << "\n--- Add New Financial Record ---\n";

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, newRecord.date);

    cout << "Enter category (e.g., Food, Rent, etc.): ";
    getline(cin, newRecord.category);

    cout << "Enter amount: ";
    while (!(cin >> newRecord.amount) || newRecord.amount <= 0)
    {
        cout << "[Error] Invalid input! Please enter a valid positive amount: ";
        validations();
    }
    validations();

    cout << "Is this Income (I) or Expense (E)? ";
    cin >> newRecord.type;
    while (newRecord.type != 'I' && newRecord.type != 'i' && newRecord.type != 'E' && newRecord.type != 'e')
    {
        cout << "[Error] Invalid type! Please select again (I/E): ";
        cin >> newRecord.type;
    }
    validations();

    newRecord.username = currentUser;
    recordsFile << newRecord.date << " " << newRecord.category << " " << newRecord.username << " "
                << newRecord.amount << " " << newRecord.type << "\n";
    recordsFile.close();

    cout << "\n[Success] Record added successfully!\n";
}

void viewRecords()
{
    ifstream recordsFile("D:\\PF LAb project Practices\\Group_no_1\\records.txt");
    Record tempRecord;
    clearScreen();
    cout << "\n--- Your Financial Records ---\n";

    bool found = false;
    cout << setw(12) << "Date" << setw(15) << "Category" << setw(10) << "Amount" << setw(8) << "Type\n";

    while (recordsFile >> tempRecord.date >> tempRecord.category >> tempRecord.username >> tempRecord.amount >> tempRecord.type)
    {
        if (tempRecord.username == currentUser)
        {
            found = true;
            cout << setw(12) << tempRecord.date
                 << setw(15) << tempRecord.category
                 << setw(10) << tempRecord.amount
                 << setw(8) << ((tempRecord.type == 'I' || tempRecord.type == 'i') ? "Income" : "Expense") << "\n";
        }
    }

    if (!found)
    {
        cout << "\n[Info] No records found for user: " << currentUser << "\n";
    }

    recordsFile.close();
}

void deleteRecord()
{
    ifstream recordsFile("D:\\PF LAb project Practices\\Group_no_1\\records.txt");
    ofstream tempFile("D:\\PF LAb project Practices\\Group_no_1\\temp.txt");

    string dateToDelete, categoryToDelete;
    Record tempRecord;
    bool found = false;

    cout << "\n--- Delete a Financial Record ---\n";
    cout << "Enter the date of the record to delete (YYYY-MM-DD): ";
    getline(cin, dateToDelete);

    cout << "Enter the category of the record to delete: ";
    getline(cin, categoryToDelete);

    while (recordsFile >> tempRecord.date >> tempRecord.category >> tempRecord.username >> tempRecord.amount >> tempRecord.type)
    {
        if (tempRecord.date == dateToDelete && tempRecord.category == categoryToDelete && tempRecord.username == currentUser)
        {
            found = true;
            cout << "\n[Success] Record deleted successfully!\n";
        }
        else
        {
            tempFile << tempRecord.date << " " << tempRecord.category << " " << tempRecord.username << " "
                     << tempRecord.amount << " " << tempRecord.type << "\n";
        }
    }

    recordsFile.close();
    tempFile.close();

    remove("D:\\PF LAb project Practices\\Group_no_1\\records.txt");
    rename("D:\\PF LAb project Practices\\Group_no_1\\temp.txt", "D:\\PF LAb project Practices\\Group_no_1\\records.txt");

    if (!found)
    {
        cout << "\n[Error] Record not found.\n";
    }
}

void calculateSummary()
{
    ifstream recordsFile("D:\\PF LAb project Practices\\Group_no_1\\records.txt");
    Record tempRecord;

    double totalIncome = 0.0, totalExpense = 0.0;

    while (recordsFile >> tempRecord.date >> tempRecord.category >> tempRecord.username >> tempRecord.amount >> tempRecord.type)
    {
        if (tempRecord.username == currentUser)
        {
            if (tempRecord.type == 'I' || tempRecord.type == 'i')
            {
                totalIncome += tempRecord.amount;
            }
            else
            {
                totalExpense += tempRecord.amount;
            }
        }
    }

    recordsFile.close();
    clearScreen();
    cout << "\n--- Financial Summary ---\n";
    cout << "Total Income: " << totalIncome << "\n";
    cout << "Total Expenses: " << totalExpense << "\n";
    cout << "Savings: " << (totalIncome - totalExpense) << "\n";
}

void financialAdvisor()
{
    ifstream recordsFile("D:\\PF LAb project Practices\\Group_no_1\\records.txt");
    Record tempRecord;
    double totalIncome = 0.0, totalExpense = 0.0;

    while (recordsFile >> tempRecord.date >> tempRecord.category >> tempRecord.username >> tempRecord.amount >> tempRecord.type)
    {
        if (tempRecord.username == currentUser)
        {
            if (tempRecord.type == 'I' || tempRecord.type == 'i')
            {
                totalIncome += tempRecord.amount;
            }
            else if (tempRecord.type == 'E' || tempRecord.type == 'e')
            {
                totalExpense += tempRecord.amount;
            }
        }
    }
    recordsFile.close();

    double savings = totalIncome - totalExpense;
    clearScreen();
    cout << "\n--- Financial Advisor ---\n";
    cout << "Total Income: " << totalIncome << "\n";
    cout << "Total Expenses: " << totalExpense << "\n";
    cout << "Savings: " << savings << "\n";

    cout << "\n--- Personalized Advice ---\n";
    if (savings > 1000)
    {
        cout << "Excellent work! With " << savings << " in savings, consider long-term investments like stocks or mutual funds.\n";
    }
    else if (savings > 0)
    {
        cout << "Good job! Your savings of " << savings << " can be enhanced by budgeting more effectively.\n";
    }
    else if (savings == 0)
    {
        cout << "You are breaking even. Aim to reduce expenses or increase income to build savings.\n";
    }
    else
    {
        cout << "You have a deficit of " << -savings << ". Urgent action is needed to reduce expenses or find additional income sources.\n";
    }
}

void mainMenu()
{
    int choice;

    do
    {
        cout << "\n=====================================";
        cout << "\n--- Personal Finance Tracker Menu ---\n";
        cout << "=====================================";

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "| 1. Add Record            |\n";
        cout << "----------------------------\n";

        cout << "| 2. View Records          |\n";
        cout << "----------------------------\n";

        cout << "| 3. Delete Record         |\n";
        cout << "----------------------------\n";

        cout << "| 4. Summary               |\n";
        cout << "----------------------------\n";

        cout << "| 5. Financail Advisor     |\n";
        cout << "----------------------------\n";

        cout << "| 6. Logout                |\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

        cout << "\nEnter your choice: ";

        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 6)
        {
            cout << "[Error] Invalid input! Please enter a valid option (1-6).\n";
            validations();
            continue;
        }

        validations();
        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            viewRecords();
            break;
        case 3:
            deleteRecord();
            break;
        case 4:
            calculateSummary();
            break;
        case 5:
            financialAdvisor();
            break;
        case 6:
            clearScreen();

            cout << "\nLogging out...\n";
            cout << "\nLogout Succesfully" << endl;
            return;
        default:
            cout << "\n[Error] Invalid choice. Try again.\n";
        }
    } while (true);
}

void validations()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
