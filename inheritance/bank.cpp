
#include <iostream>
#include <utility>

using namespace std;

// Abstract class  (interface-style)
class AccountInterface {
public:
    // Pure Virtual functions (Use = 0)
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void display() const = 0;
    virtual ~AccountInterface() = default;  // Use = default; for the destructor if no custom cleanup is needed.
};

// Bank class forward declaration
class Bank;

class Account: public AccountInterface {
private:
    static int totalAccounts;
    string owner;
    double balance;
public:
    // Copy (or const reference) constructor
    // Account(const string& name, const double initial) : owner(name), balance(initial){
    //     totalAccounts++;
    //     cout << "Account created for "<< owner << " with Balance: ksh " << balance << endl;
    // }
    // Move constructor
    Account(string name, const double initial) : owner(move(name)) , balance(initial) {
        totalAccounts++;
        cout << "Account created for "<< owner << " with Balance: ksh " << balance << endl;
    }
    void deposit(const double amount) override {
        balance += amount;
        cout << owner << " deposited " << amount << ". New Balance: " << balance << endl;
    }

    void withdraw(const double amount) override {
        if (amount <=balance) {
            balance -= amount;
            cout << owner << " withdrew ksh"<< amount << ". New Balance: " << balance << endl;
        }
        else {
            cout << owner << "has insufficient balance!" << endl;
        }
    }

    void display() const override {
        cout << "Owner: " << owner << " | Balance: " << balance << endl;
    }

    static int getTotalAccounts() {
        return totalAccounts;
    }

    friend class Bank;

    // Base class has virtual ~AccountInterface() thus overrude is recommended
    ~Account() override {
        cout << "Account  closed for " << owner << endl;
    }
};


// Initialize static variable
int Account::totalAccounts = 0;

// Friend to Account
class Bank {
private:
    Account* accounts[50] = {}; // Fixed size array, sets all elements to nullptr
    int accountCount;

public:
    Bank() : accountCount(0) {
        /** auto : Let the compiler deduce the type automatically.
        * accounts is a C-style array of Account* (i.e., Account* accounts[50];)
        * Each account is a reference to an element of that array (which is of type Account*&)
        * auto& deduces to Account*& — a reference to a pointer to Account
        * So you're iterating through each pointer in the array and setting it to nullptr.
        */
        for (auto & account : accounts) {
            account = nullptr;
        }
    }

    void openAccount(const string& name, const double initial) {
        if (accountCount >= 50) {
            cout << "Maximum number of accounts reached!" << endl;
            return;
        }
        accounts[accountCount++] = new Account(name, initial);
    }

    void performOperation() const {
        if (accountCount >= 2) {
            accounts[0] -> deposit(500);
            accounts[1] -> deposit(1000);
        }
    }

    void showAllAccounts() const {
        for (int i = 0; i < accountCount; i++) {
            accounts[i] -> display();
        }
    }

    ~Bank() {
        for (auto& acc : accounts) {
            delete acc;
        }
    }
};

int main () {
    Bank myBank;
    myBank.openAccount("John Snow", 1000);
    myBank.openAccount("Hellen Kelly", 5000);

    myBank.performOperation();
    myBank.showAllAccounts();

    cout << "Total Accounts: "<< Account::getTotalAccounts() << endl;
    return 0;
}
