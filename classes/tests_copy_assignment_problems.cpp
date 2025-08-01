#include <iostream>
#include <cstring>
using namespace std;

class Person {
    char* name;
public:
    Person(const char* inputName) {
        name = new char[strlen(inputName) + 1];
        strcpy(name, inputName);
    }

    // Copy constructor only
    Person(const Person& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    // ❌ No copy assignment operator

    ~Person() {
        delete[] name;
    }

    void display() const {
        cout << "Name: " << name << endl;
    }
};

int main() {
    Person p1("Alice");
    Person p2("Bob");

    p2 = p1; // ⚠️ Compiler provides default shallow copy assignment

    p1.display();  // Alice
    p2.display();  // Alice (so far, looks okay)

    // Modify p1's name manually (unsafe but for demo)
    p1 = "Zoe"; // not valid without const char* assignment, will crash or corrupt

    // Both p1 and p2 may now show Zoe or garbage depending on state
    p1.display();
    p2.display(); // corrupted or duplicated, possibly crash at destructor

    return 0;
}
