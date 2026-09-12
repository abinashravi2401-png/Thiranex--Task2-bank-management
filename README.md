#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

class BankAccount {
private:
    int accountNumber;
    char name[50];
    double balance;

public:
    void createAccount() {
        std::cout << "\nEnter Account Number: ";
        std::cin >> accountNumber;
        std::cin.ignore();
        std::cout << "Enter Account Holder Name: ";
        std::cin.getline(name, 50);
        std::cout << "Enter Initial Deposit Amount: $";
        std::cin >> balance;
        std::cout << "\nAccount successfully created!\n";
    }

    void displayAccount() const {
        std::cout << "\nAccount Number : " << accountNumber;
        std::cout << "\nAccount Holder : " << name;
        std::cout << "\nCurrent Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "\n$" << amount << " deposited successfully. Updated Balance: $" << balance << "\n";
        } else {
            std::cout << "\nInvalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "\nInsufficient balance! Current Balance: $" << balance << "\n";
        } else if (amount <= 0) {
            std::cout << "\nInvalid withdrawal amount.\n";
        } else {
            balance -= amount;
            std::cout << "\n$" << amount << " withdrawn successfully. Remaining Balance: $" << balance << "\n";
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

// File handling functions
void writeAccountToFile();
void displayAccountDetails(int accNum);
void handleDeposit(int accNum);
void handleWithdrawal(int accNum);

int main() {
    int choice;
    int accNum;

    do {
        std::cout << "\n===================================";
        std::cout << "\n     BANK MANAGEMENT SYSTEM";
        std::cout << "\n===================================";
        std::cout << "\n1. Create New Account";
        std::cout << "\n2. Deposit Money";
        std::cout << "\n3. Withdraw Money";
        std::cout << "\n4. Balance Check / Account Details";
        std::cout << "\n5. Exit";
        std::cout << "\nChoose an option (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                writeAccountToFile();
                break;
            case 2:
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                handleDeposit(accNum);
                break;
            case 3:
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                handleWithdrawal(accNum);
                break;
            case 4:
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                displayAccountDetails(accNum);
                break;
            case 5:
                std::cout << "\nThank you for using the Banking Application. Goodbye!\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void writeAccountToFile() {
    BankAccount ac;
    std::ofstream outFile("accounts.dat", std::ios::binary | std::ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
    outFile.close();
}

void displayAccountDetails(int accNum) {
    BankAccount ac;
    std::ifstream inFile("accounts.dat", std::ios::binary);
    bool found = false;

    if (!inFile) {
        std::cout << "\nFile could not be opened. No records exist yet.\n";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        if (ac.getAccountNumber() == accNum) {
            ac.displayAccount();
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) {
        std::cout << "\nAccount number " << accNum << " does not exist.\n";
    }
}

void handleDeposit(int accNum) {
    BankAccount ac;
    std::fstream file("accounts.dat", std::ios::binary | std::ios::in | std::ios::out);
    bool found = false;

    if (!file) {
        std::cout << "\nFile could not be opened. No records exist yet.\n";
        return;
    }

    while (!file.eof() && file.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        if (ac.getAccountNumber() == accNum) {
            double amount;
            std::cout << "Enter Deposit Amount: $";
            std::cin >> amount;
            ac.deposit(amount);

            int pos = (-1) * static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, std::ios::cur);
            file.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        std::cout << "\nAccount number " << accNum << " does not exist.\n";
    }
}

void handleWithdrawal(int accNum) {
    BankAccount ac;
    std::fstream file("accounts.dat", std::ios::binary | std::ios::in | std::ios::out);
    bool found = false;

    if (!file) {
        std::cout << "\nFile could not be opened. No records exist yet.\n";
        return;
    }

    while (!file.eof() && file.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        if (ac.getAccountNumber() == accNum) {
            double amount;
            std::cout << "Enter Withdrawal Amount: $";
            std::cin >> amount;
            ac.withdraw(amount);

            int pos = (-1) * static_cast<int>(sizeof(BankAccount));
            file.seekp(pos, std::ios::cur);
            file.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        std::cout << "\nAccount number " << accNum << " does not exist.\n";
    }
}
