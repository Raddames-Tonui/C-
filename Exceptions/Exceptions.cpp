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
class Animal {
public:
    virtual void speak() { cout << "Animal\n"; }
};

class Dog : public Animal {
public:
    void speak() override { cout << "Dog\n"; }
};

void objectSlicing() {
    Dog d;
    Animal a = d; // Object slicing
    a.speak(); // Calls Animal::speak, not Dog::speak
}

// ---------- DANGLING POINTER ----------
int* getDanglingPointer() {
    int x = 42;
    return &x; // Returns address of local variable
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
    // Uncomment one at a time to see the error in action

    SyntaxErrorExample s; s.sayHello();
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
