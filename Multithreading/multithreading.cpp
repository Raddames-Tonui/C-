#include <charconv>
#include <thread>
#include <iostream>
#include <mutex>


using namespace std;
// thread thread_name(callable);
// Callables

// Function Pointer
void func(string name) {
    cout << "Hello from thread!" << name << endl;
}

// function object (functor)
class SumFunctor {
public:
    int n;
    SumFunctor(int a) : n(a) {}
    // Overload () to make it callable
    void operator()() const {
        cout << n << endl;
    }
};


class MyClass {
public:
    void printNonStatic() {
        cout << "This is a non static function" << endl;
    }

    void printValues(float f) {
        cout << "f = " << f << endl;
    }

    static void printStatic() {
        cout << "This is static function" << endl;
    }

    static void printStaticValue(int num) {
        cout << "Static func with num = " << num << endl;
    }


};



int main() {

    // a) Functions
    thread t (func, "james");
    // wait for the thread to complete
    t.join();
    cout << "Main thread finished!" << endl;


    // b) Lambda Expression
    int n = 5;

    thread p([](int n) {
        cout << n << endl;
    }, n );

    p.join();

    // c) Function objects
    thread f(SumFunctor(3));

    f.join();

    // d) static and non static Member functions
    // static requires an object
    MyClass obj;
    thread s1(&MyClass::printNonStatic, &obj);
    s1.join();
    thread s2(&MyClass::printValues, &obj, 5.6);
    s2.join();

    // Static member func can be called without object
    thread s3(&MyClass::printStatic);
    s3.join();
    thread s4(&MyClass::printStaticValue, 26);
    s4.join();


    return 0;
}