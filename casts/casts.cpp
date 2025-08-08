#include <iostream>
using namespace std;

class Base { virtual void dummy() {} };
class Derived : public Base {};

int main() {
    int x = 42;
    double y = static_cast<double>(x); // static_cast

    double z = 3.14;
    int a = (int)z;                     // C-style cast

    // Allocate basePtr dynamically
    Base* basePtr = new Derived();
    // Use dynamic_cast to safely cast to Derived*
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // dynamic_cast

    // No need to delete derivedPtr separately; delete basePtr is sufficient
    delete basePtr;

    // const_cast example: removing constness - only safe if original data is non-const
    const int c = 10;
    int& ref = const_cast<int&>(c);
    // Modifying c here is undefined behavior, so avoid doing it on truly const data
    cout << ref << endl; // printing value is safe but modifying is not recommended

    // Remove constness from a pointer to const int
    const int someInt = 5;
    const int* pConst = &someInt;
    int* pNonConst = const_cast<int*>(pConst);
    // Modifying a value that is originally const leads to undefined behavior
    // *pNonConst = 42; // Do not do this on truly const data

    // Demonstration: creating a non-const copy
    int nonConstCopy = *pNonConst; // Safe to copy, but do NOT modify the original const object

    // const_ref example
    const int someIntRef = 6;
    const int& constRef = someIntRef;
    cout << "someIntRef: " << someIntRef << " constRef: " << constRef << endl;

    int& ref1 = const_cast<int&>(constRef);
    ref1 = 100; // This is safe here because original was non-const
    cout << "ref1: " << ref1 << endl;

    // reinterpret_cast example - use carefully
    int* p = reinterpret_cast<int*>(0x1234);
    cout << "Pointer reinterpret_cast result: " << p << endl;

    // No need to delete stack variables
    // delete pNonConst;  // Don't delete pointers pointing to stack data
    // delete pConst;     // Same here, can't delete pointers to non-dynamic memory

    cout << "x: " << x << ", y: " << y << endl;

    return 0;
}