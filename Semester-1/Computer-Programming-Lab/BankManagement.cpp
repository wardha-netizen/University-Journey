#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;

struct account {
    string number = "";
    string name = "";
    char type = '\0';
    int balance = 0;
} accounts[3];

void saveAccountsToFile();
void loadAccountsFromFile();

void intro() {
    cout << "\n\n MADE BY : WARDHA KHALID ";
    cout << "\n UNIVERSITY : BAHRIA UNIVERSITY KARACHI";
    cin.ignore();
    cin.get();
}

void openAccount() {
    loadAccountsFromFile();
    account newAcc;

    cout << "\nPlease Enter The account No. : ";
    cin >> newAcc.number;
    cin.ignore();
    cout << "\nPlease Enter The Name of The account Holder: ";
    getline(cin, newAcc.name);

    bool isValidInput = false;
    do {
        cout << "Please Enter Account Type (C for Current / S for Saving): ";
        cin >> newAcc.type;
        newAcc.type = toupper(newAcc.type);
        isValidInput = (newAcc.type == 'C' || newAcc.type == 'S');
        if (!isValidInput) cout << "Invalid Input!. Please try again.\n";
    } while (!isValidInput);

    cout << "\nEnter Initial amount (>=440 for Saving, >=1000 for Current): ";
    cin >> newAcc.balance;

    while ((newAcc.type == 'S' && newAcc.balance < 440) || (newAcc.type == 'C' && newAcc.balance < 1000)) {
        cout << "Invalid initial deposit. Please re-enter: ";
        cin >> newAcc.balance;
    }

    bool added = false;
    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == "") {
            accounts[i] = newAcc;
            added = true;
            break;
        }
    }

    if (added) {
        cout << "\nAccount Created Successfully.\n";
        saveAccountsToFile();
    }
    else {
        cout << "\nBank is full (Max 3 accounts).\n";
    }
}

void display() {
    loadAccountsFromFile();
    cout << "\n" << setfill('=') << setw(60) << "" << endl;
    cout << "Displaying Information of All Account Holders" << endl;
    cout << setfill('=') << setw(60) << "" << setfill(' ') << endl;

    cout << left << setw(15) << "Account No." << setw(20) << "Name" << setw(10) << "Type" << setw(15) << "Balance" << endl;

    for (int i = 0; i < 3; i++) {
        if (accounts[i].number != "") {
            cout << left << setw(15) << accounts[i].number
                << setw(20) << accounts[i].name
                << setw(10) << accounts[i].type
                << setw(15) << accounts[i].balance << endl;
        }
    }
}

void updateDeposit() {
    loadAccountsFromFile();
    string accNum;
    int amount;
    cout << "\nEnter account number for deposit: ";
    cin >> accNum;

    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == accNum) {
            cout << "Enter deposit amount: ";
            cin >> amount;
            if (amount > 0) {
                accounts[i].balance += amount;
                saveAccountsToFile();
                cout << "\nDeposit successful!\n";
                return;
            }
        }
    }
    cout << "Account not found or invalid amount.\n";
}

void withdraw() {
    loadAccountsFromFile();
    string accNum;
    int amount;
    cout << "\nEnter account number for withdrawal: ";
    cin >> accNum;

    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == accNum) {
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            if (amount > 0 && amount <= accounts[i].balance) {
                accounts[i].balance -= amount;
                saveAccountsToFile();
                cout << "\nWithdrawal successful!\n";
                return;
            }
            else {
                cout << "Insufficient balance or invalid amount.\n";
                return;
            }
        }
    }
    cout << "Account not found.\n";
}

void deleteAccount() {
    loadAccountsFromFile();
    string accNum;
    cout << "\nEnter account number to delete: ";
    cin >> accNum;

    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == accNum) {
            accounts[i] = account(); // Resets to empty
            saveAccountsToFile();
            cout << "Account deleted successfully!\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

void saveAccountsToFile() {
    ofstream outfile("accounts.txt", ios::trunc);
    for (int i = 0; i < 3; i++) {
        if (accounts[i].number != "") {
            outfile << accounts[i].name << endl;
            outfile << accounts[i].type << endl;
            outfile << accounts[i].number << endl;
            outfile << accounts[i].balance << endl;
        }
    }
    outfile.close();
}

void loadAccountsFromFile() {
    ifstream infile("accounts.txt");
    if (!infile) return;

    for (int i = 0; i < 3; i++) accounts[i] = account(); // Clear array first

    int i = 0;
    string name, type, num, bal;
    while (getline(infile, name) && i < 3) {
        getline(infile, type);
        getline(infile, num);
        getline(infile, bal);

        accounts[i].name = name;
        accounts[i].type = type[0];
        accounts[i].number = num;
        accounts[i].balance = stoi(bal);
        i++;
    }
    infile.close();
}

int main() {
    int choice;
    do {
        cout << "\n\n\tMAIN MENU";
        cout << "\n\t01. NEW ACCOUNT";
        cout << "\n\t04. DISPLAY ALL";
        cout << "\n\t05. DEPOSIT";
        cout << "\n\t06. WITHDRAW";
        cout << "\n\t07. DELETE";
        cout << "\n\t08. EXIT";
        cout << "\n\tSelect (1-8): ";
        cin >> choice;

        switch (choice) {
        case 1: openAccount(); break;
        case 4: display(); break;
        case 5: updateDeposit(); break;
        case 6: withdraw(); break;
        case 7: deleteAccount(); break;
        }
    } while (choice != 8);
    return 0;
}