// bank.cpp
// Демонстрация базового синтаксиса ООП

#include <iostream>
using namespace std;

class BankAccount {
    private:
        double balance;
    public:
        BankAccount(double openingBalance) {
            balance = openingBalance;
        }
        void deposit(double amount) {
            balance = balance + amount;
        }
        void withdraw(double amount) {
            balance = balance - amount;
        }
        void display() {
            cout << "\nbalance = " << balance;
        }
};

class BankApp {
    public:
        static void main() {
            BankAccount* bal = new BankAccount(100.00);

            cout << "Before transactions. ";
            bal->display();
            
            bal->deposit(74.35);
            bal->withdraw(20.00);

            cout << "\nAfter transactions. ";
            bal->display();
            cout << endl;
        }
};

int main() {
    BankApp::main();
    return 0;
}