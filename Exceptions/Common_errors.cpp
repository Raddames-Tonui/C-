#include <iostream>
using namespace std;

// ---------- SYNTAX ERROR ----------
// Missing semicolon will trigger compile-time error
class SyntaxErrorExample {
public:
    void sayHello() {
        cout << "Hello" << endl
    }
};

// ---------- UNDECLARED IDENTIFIER ----------
void undeclaredIdentifier() {
    x = 10; // 'x' not declared
}

// ---------- TYPE MISMATCH ----------
void typeMismatch() {
    int a = "String"; // Assigning string to int
}

// ---------- DIVISION BY ZERO ----------
void divideByZero() {
    int a = 10;
    int b = 0;
    int result = a / b; // Runtime crash
    cout << result << endl;
}

// ---------- NULL POINTER DEREFERENCE ----------
void nullPointer() {
    int* ptr = nullptr;
    *ptr = 100; // Segmentation fault
}

// ---------- MEMORY LEAK ----------
void memoryLeak() {
    int* arr = new int[100]; // Allocated memory
    // Forgot to delete[] arr — leak
}

// ---------- ARRAY OUT OF BOUNDS ----------
void outOfBounds() {
    int nums[3] = {1, 2, 3};
    nums[10] = 100; // Undefined behavior
}

// ---------- INFINITE RECURSION ----------
void recurse() {
    recurse(); // Stack overflow
}

// ---------- UNINITIALIZED VARIABLE ----------
void uninitializedVar() {
    int x;
    cout << x << endl; // Garbage value
}

// ---------- CONSTRUCTOR MISUSE ----------
class NoDefaultConstructor {
public:
    NoDefaultConstructor(int x) { cout << "Constructor called\n"; }
};

void constructorMisuse() {
    NoDefaultConstructor obj; // Error: no default constructor
}

// ---------- OBJECT SLICING ----------
//Happens when a derived class object (Dog)
// is assigned to a base class object (Animal) by value.
class Animal {
public:
    virtual void speak() { cout << "Animal\n"; }
    virtual ~Animal();
};

class Dog : public Animal {
public:
    void speak() override { cout << "Dog\n"; }
    ~Dog() override { cout << "~Dog\n"; }
};

void objectSlicing() {
    Dog d;
    Animal a = d; // Object slicing  (Only the Animal part of d is copied — the Dog-specific parts are "sliced off".)
    a.speak(); // Calls Animal::speak, not Dog::speak

/** Use pointers or references to base class To Preserve Polymorphism::
        Animal* a = new Dog();
        a->speak(); // Outputs "Dog"
*    ---OR ---
        Dog d;
        Animal& a = d; // No slicing
        a.speak();     // Outputs "Dog"
*/
}

// ---------- DANGLING POINTER ----------
int* getDanglingPointer() {
    int x = 42;
    return &x; // BAD: x is a local variable, gets destroyed after function returns

}

void useDanglingPointer() {
    int* p = getDanglingPointer();
    cout << *p << endl; // Undefined behavior
}

// ---------- ACCESS VIOLATION ----------
class PrivateExample {
private:
    int secret = 123;
};

void accessViolation() {
    PrivateExample obj;
    cout << obj.secret; // Error: ‘secret’ is private
}

// ---------- MAIN ----------
int main() {
    // Uncomment

    // SyntaxErrorExample s; s.sayHello();
    // undeclaredIdentifier();
    // typeMismatch();
    // divideByZero();
    // nullPointer();
    // memoryLeak();
    // outOfBounds();
    // recurse();
    // uninitializedVar();
    // constructorMisuse();
    // objectSlicing();
    // useDanglingPointer();
    // accessViolation();

    return 0;
}
