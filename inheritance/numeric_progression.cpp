#include <iostream>

using std::cout;
using std::endl;


// Base Class: Generic Progression

class Progression {
protected:
    long first; // First value
    long cur;   // Current value

public:
    Progression(long f = 0) : first(f), cur(f) {}
    virtual ~Progression() {}

    void printProgression(int n); // Print first n values
    virtual void print() {
        cout << "This is progression class" << endl;
    }

protected:
    virtual long firstValue();    // Reset to first value
    virtual long nextValue() = 0;     // Advance to next value
};

// Print first n values of the progression
void Progression::printProgression(int n) {
    cout << firstValue(); // First value

    for (int i = 2; i <= n; ++i)
        cout << " " << nextValue();

    cout << endl;
}

long Progression::firstValue() {
    cur = first;
    return cur;
}



// Derived Class: Arithmetic Progression

class ArithProgression : public Progression {
protected:
    long inc; // Increment

public:
    ArithProgression(long increment = 1)
        : Progression(), inc(increment) {}

    void print() override {
        cout << "This is Arithprogression class" << endl;
    }

protected:
    long nextValue() override {
        cur += inc;
        return cur;
    }
};



// Derived Class: Fibonacci Progression

class FibonacciProgression : public Progression {
protected:
    long second; // Second value
    long prev;   // Previous value

public:
    explicit FibonacciProgression(long f = 0, long s = 1)
        : Progression(f), second(s), prev(s - f) {}

    void print() override {
        cout << "This is FibonacciProgression class" << endl;
    }

protected:
    long firstValue() override {
        cur = first;
        prev = second - first;
        return cur;
    }

    long nextValue() override {
        long temp = prev;
        prev = cur;
        cur += temp;
        return cur;
    }
};

class GeomProgression : public Progression {
protected:
    long base;

public:
    explicit GeomProgression(long b = 2) : Progression(1), base(b) {}
    void print() override {
        cout << "This is GeomProgression class" << endl;
    }
protected:
    long nextValue() override {
        cur *= base;
        return cur;
    }
};



int main() {
    Progression* prog;

    // Arithmetic Progression
    cout << "Arithmetic progression with default increment:\n";
    prog = new ArithProgression();
    prog->printProgression(10);
    delete prog;

    cout << "Arithmetic progression with increment 5:\n";
    prog = new ArithProgression(5);
    prog->printProgression(10);
    delete prog;

    // Geometric Progression
    cout << "Geometric progression with default base:\n";
    prog = new GeomProgression();  // base = 2 by default
    prog->printProgression(10);
    delete prog;

    cout << "Geometric progression with base 3:\n";
    prog = new GeomProgression(3);
    prog->printProgression(10);
    delete prog;

    // Fibonacci Progression
    cout << "Fibonacci progression with default start values:\n";
    prog = new FibonacciProgression();
    prog->printProgression(10);
    delete prog;

    cout << "Fibonacci progression with start values 4 and 6:\n";
    prog = new FibonacciProgression(4, 6);
    prog->printProgression(10);
    delete prog;


    //------ dynamic binding or runtime polymorphism.--------
    Progression *ptr2 = new Progression();
    ptr2 -> print(); // This is progression class

    Progression* ptr = new FibonacciProgression(4, 5);
    ptr -> print(); // This is FibonacciProgression class

    ArithProgression p1;
    p1.print(); //This is Arithprogression class

    cout << "------CASTING------" << endl;
    Progression* basePtr = new ArithProgression();
    /**    basePtr -> print();
     *  This is Arithprogression class Because print() is virtual else
     *  It would print This is progression class if it wasn't virtual
     */
    basePtr -> print();

            // Explicit cast to derived class
    ArithProgression* arithPtr= dynamic_cast<ArithProgression*>(basePtr);
    arithPtr -> print(); //This is Arithprogression class


    delete ptr;
    delete ptr2;
    delete basePtr;
    return 0;
}
