

#include <string.h>
#include <iostream>
using namespace std;

class  Person {
private:
    char* name;
public:
    // constructor
    Person(const char* inputName) {
        name = new char[strlen(inputName) + 1]; //(allocate memory) creates space for all characters plus 1 extra byte for the null character '\0
        strcpy(this->name, inputName); // (copy content) strcpy(destination, source)
    }

    // 1. User Defined copy constructor
    Person(const Person& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        cout << "Copy Constructor called: " << endl;
    }

    // 2. Copy assignment operator
    Person& operator=(const Person& other) {
        /**
         *Without the check, it would:
         *delete[] name → deallocates its own memory
         *Try to copy from itself → crashes or copies garbage
         */
        if (this == &other) return *this;
        delete[] name; // clean old memory
        name = new char[strlen(other.name) + 1]; // allocate memory
        strcpy(this->name, other.name);   // copy
        return *this; //  allow chaining like a = b = c;
    }

    // 3. Move Constructor


    // 5. Destructor
    ~Person() {
        delete[] name;
    }

    void display() {
        cout << "Name: " << name << endl;
    }
};


int main() {
    Person p1("Raddames");
    Person p2 = "John";
    p1.display();
    p2.display();

    p2 = p1;

    p2 = "James";
    p1.display();
    p2.display();

}