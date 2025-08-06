#include <iostream>
#include <string>
#include <utility>
using namespace std;

// Base class
class Account {
protected:
    string owner;
    double balance;

public:
    Account(string owner, double bal) : owner(std::move(owner)), balance(bal) {}

    virtual void display() const {
        cout << "Owner: " << owner << ", Balance: Ksh" << balance << endl;
    }

    virtual void deposit(const double amount) {
        balance += amount;
        cout << owner << " deposited Ksh" << amount << ", new balance: Ksh" << balance << endl;
    }

    virtual void withdraw(const double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << owner << " withdrew Ksh" << amount << ", new balance: Ksh" << balance << endl;
        } else {
            cout << "Insufficient funds for " << owner << endl;
        }
    }

    virtual ~Account() = default;
};

// Derived class
// final in class ->Prevent inheritance,  Enable compiler optimizations  Enforce design intent
class SavingsAccount final : public  Account {
protected:
    double interestRate;
public:
    SavingsAccount(const string& o, const double b, const double rate)
        : Account(o, b), interestRate(rate) {}

    void addInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << owner << " earned Ksh" << interest << " in interest. New balance: Ksh" << balance << endl;
    }

    void display() const override {
        cout << "[Savings] ";
        Account::display();
        cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
    }
};


class CheckingAccount final : public  Account {
protected:
    double overdraftLimit;

public:
    CheckingAccount(const string& o, const double b, const double limit)
        : Account(o, b), overdraftLimit(limit) {}

    void withdraw(const double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            cout << owner << " withdrew Ksh" << amount << " (Overdraft allowed), New balance: Ksh" << balance << endl;
        } else {
            cout << "Overdraft limit exceeded for " << owner << endl;
        }
    }

    void display() const override {
        cout << "[Checking] ";
        Account::display();
        cout << "Overdraft Limit: Ksh" << overdraftLimit << endl;
    }
};

int main() {
    cout << "---- Savings Account Test ----" << endl;
    SavingsAccount savings("Alice", 1000.0, 0.05);
    savings.display();
    savings.deposit(200);
    savings.withdraw(300);
    savings.addInterest();
    savings.display();

    cout << "\n---- Checking Account Test ----" << endl;
    CheckingAccount checking("Bob", 1000.0, 500.0);
    checking.display();
    checking.deposit(150);
    checking.withdraw(1400);
    checking.withdraw(200);
    checking.display();

    return 0;
}
