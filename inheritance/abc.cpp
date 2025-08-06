#include <iostream>
using namespace std;

// 1. Basic Multiple Inheritance – No Conflicts
class Logger {
public:
    void log() {
        cout << "Logging...\n";
    }
};

class Notifier {
public:
    void notify() {
        cout << "Notifying...\n";
    }
};

class System : public Logger, public Notifier {
    // Inherits both log() and notify()
};


// 2. Function Name Conflict – Need Scope Resolution
class A {
public:
    void show() {
        cout << "A::show\n";
    }
};

class B {
public:
    void show() {
        cout << "B::show\n";
    }
};

class C : public A, public B {};

// 3. Virtual Functions in Multiple Inheritance
class D {
public:
    virtual void display() {
        cout << "D::display\n";
    }
};

class E {
public:
    virtual void display() {
        cout << "E::display\n";
    }
};

class F : public D, public E {
public:
    void display() override {
        cout << "F::display\n";
    }
};


int main() {

    System sys;
    sys.log();     // From Logger
    sys.notify();  // From Notifier


    // Call Ambiguous Function
    // C obj;
    // obj.show(); ❌ error: ambiguous

    // obj.A::show(); // ✅ specify scope
    // obj.B::show(); // ✅

    //  Call via Pointer
    // F obj1;
    // D* dPtr = &obj1;
    // E* ePtr = &obj1;

    // dPtr->display(); // F::display
    // ePtr->display(); // F::display

    // Direct Call Using F
    F obj;
    obj.display(); // Ambiguous ❌
    obj.D::display(); // ✅ Resolves to F::display()
    obj.E::display(); // ✅ Resolves to F::display()

//     ✅ 2. Using Pointers
// A. Base Class Pointer (D*)

    F ptrss;
    D* dPtrs = &ptrss;
    dPtrs->display(); // ✅ Calls F::display


    return 0;
}