#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Custom exceptions
class ShoppingListTooSmallException : public exception {
public:
    const char* what() const noexcept override {
        return "Shopping list is too small!";
    }
};

class OutOfMoneyException : public exception {
public:
    const char* what() const noexcept override {
        return "You are out of money!";
    }
};

class BurntCookiesException : public exception {
public:
    const char* what() const noexcept override {
        return "The cookies were burnt!";
    }
};

// Function declarations with exception specifications
void goShopping() throw(ShoppingListTooSmallException, OutOfMoneyException);
void makeCookiesForTA() throw(BurntCookiesException);
void getReadyForClass() throw(ShoppingListTooSmallException, OutOfMoneyException, BurntCookiesException);

// Function definitions

void goShopping() throw(ShoppingListTooSmallException, OutOfMoneyException) {
    int listSize = 0;
    int money = 0;

    if (listSize < 3) {
        throw ShoppingListTooSmallException();
    }

    if (money <= 0) {
        throw OutOfMoneyException();
    }

    cout << "Shopping done successfully.\n";
}

void makeCookiesForTA() throw(BurntCookiesException) {
    bool ovenTooHot = true;

    if (ovenTooHot) {
        throw BurntCookiesException();
    }

    cout << "Cookies made successfully.\n";
}

void getReadyForClass() throw(ShoppingListTooSmallException, OutOfMoneyException, BurntCookiesException) {
    goShopping();         // Might throw ShoppingListTooSmallException or OutOfMoneyException
    makeCookiesForTA();   // Might throw BurntCookiesException
}

int main() {
    try {
        // getReadyForClass();
        // makeCookiesForTA();
        getReadyForClass();
    } catch (const ShoppingListTooSmallException& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const OutOfMoneyException& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const BurntCookiesException& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Unknown error: " << e.what() << endl;
    }

    return 0;
}
