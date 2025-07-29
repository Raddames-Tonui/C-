#include <iostream>
using namespace std;

// Pass by value
void useValue (int a, int b, int c)
{
    a*=2;
    b*=2;
    c*=2;
}

// Pass by reference
void useReference (int& a, int& b, int& c) {
    a*=2;
    b*=2;
    c*=2;
}

// Pass by pointer
void usePointer (int* a, int* b, int* c) {
    *a*=2;
    *b*=2;
    *c*=2;
}

void passBy() {
    // Pass by value, reference and pointers
    int x = 1, y = 3, z = 7;
    useValue(x, y, z); // remains same  x=1, y=3, z=7
    cout << "x=" << x << ", y=" << y << ", z=" << z << endl;

    useReference (x, y, z); // doubles x=2, y=6, z=14
    cout << "x=" << x << ", y=" << y << ", z=" << z << endl;

    usePointer(&x, &y, &z); // doubles x=4, y=12, z=28
    cout << "x=" << x << ", y=" << y << ", z=" << z << endl;
}


// RECURSIVE FUNCTION -
// A function that calls itself to solve smaller parts of a problem.
long factorial (long a) {
    if (a > 1)
        return a * factorial(a-1);
    return 1;
}

// Default arguments
void defaultFunction(int a = 10);

// INLINE FUNCTIONS -
// Suggests to the compiler to insert code directly to avoid a function call.
inline int square(int x) {
    return x * x;
}

class A {
public:
    static inline int square(int x);
};

inline  int A::square(int x) {
     return x * x;
}

// STATIC keyword
// static variable
void staticFunc() {
    static int count = 0;     // Static variable
    // The value will be updated and carried over
    // to the next function call
    count++;
    cout << count << endl;
}


// VIRTUAL FUNCTION -
// Allows runtime polymorphism — the actual function called depends on the object type.
//A virtual function is a function in a base class meant to be overridden in derived classes.
// But it can have a body in the base.
class Base {
public:
    virtual ~Base() {
        cout << "Base destructor \n";
    }

    // Virtual function
    virtual void display () {
        cout << "Base class function \n";
    }
};

class Derived: public Base {
public:
    ~Derived() override {
        cout << "Derived destructor \n";
    }

    // Overriding the Base::display() function
    void display() override {
        cout << "Derived class function \n";
    }
};

void virtualFunc () {
    // Allocate Derived on the heap, so it can be safely deleted later.
    Base* basePtr = new Derived();

    // Calling the display function using base class pointer
    basePtr->display();

    // Now it's safe to delete, since the object was allocated with new.
    delete basePtr;
    basePtr = nullptr;
}



// PURE VIRTUAL FUNCTIONS (Abstract Function)-
// Defines an interface — must be overridden in a derived class.
// It also makes the class abstract, meaning you cannot instantiate it directly.
class Animal {
public:
    virtual ~Animal() = default;

    virtual void speak() = 0; // Pure virtual
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Dog barks \n";
    }
};

void pureVirtualFunction() {
    Animal* animal = new Dog();
    animal -> speak();
    delete animal;
    animal = nullptr;
}

// FRIEND FUNCTION
// Can access private members of a class even though it’s not part of the class.
class  Box {
    int width;
public:
    explicit Box(const int w) : width(w){} // explicit — stops C++ from using this constructor for implicit conversions:
    friend void showWidth(Box b);
};

void showWidth(Box b) {
    cout << "Box Width: " << b.width << endl;
};

// TEMPLATE FUNCTION
// Generic function that works with any type.
// Template function to find the maximum of two values
template <typename T>
T getMax (T a, T b) {
    return (a > b) ? a : b;
}

void templateFunc() {
    cout << "Max of 3 and 7: " << getMax(3, 7) << endl;          // int
    cout << "Max of 3.5 and 2.1: " << getMax(3.5, 2.1) << endl;  // double
    cout << "Max of 'a' and 'z': " << getMax('a', 'z') << endl;  // char
    cout << "Max of strings: " << getMax(string("apple"), string("banana")) << endl;  // string
}


int main() {
    // Pass by Value, reference and Pointer
    passBy();

    // Recursive
    long f =9;
    cout << f << "! = " <<factorial(f)<< endl;

    // Default value
    defaultFunction();
    defaultFunction(500);

    int num = 5;

    // calling inline function
    int res = square(num);
    cout << res << endl;

    // static
    for (int i = 0; i < 5; i++)
        staticFunc();


    // Virtual func
    virtualFunc();

    // Pure Virtual Func
    pureVirtualFunction();

    // Friend func
    showWidth(Box(5));

    // Template func
    templateFunc();

    return 0;
}


// For displaying default arguments
void defaultFunction(int a) {
    cout << a << endl;
}



