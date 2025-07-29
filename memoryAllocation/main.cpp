#include <iostream>

using namespace std;

// Memory Allocation (STACK and HEAP)
int total;

int squareOfSum(int x, int y);
int pointersTutorial();
int pointerVsReference();
int memoryManagement();

int main() {
    int a = 8, b = 4;
    total = squareOfSum(a, b);

    std::cout << "Square of Sum = " << total << std::endl;
    memoryManagement();

    // pointersTutorial();

    // Pointer vs reference tutorial
    // pointerVsReference();


    return 0;
}

int square(int x) {
    return x * x;
}

int squareOfSum(int x, int y) {
    const int z = square(x) + square(y);
    return z;
}



// -------------- Memory Management ----------------

int memoryManagement () {
    int* p = new int(5);   // allocates on heap
    delete p;               // free memory

    // For Arrays
    int* arr = new int[10];
    delete[] arr;

    int x[5] = {1, 2, 3, 4, 5};
    cout << x[0] << endl;
    cout << x[9] << endl;
    cout << *x << endl;
    cout << *(x+2) << endl;

    return 0;
}


// ------------  POINTERS -----------------
// ------------a) Pointer vs Reference --------------

int pointerVsReference() {

    //  -------------- POINTER -------------
    int* ptr;
    cout << "Initial value of ptr: " << &ptr << endl;

    // variables
    int var = 7;
    int foo = 21;
    cout << "variable var : " << var  << endl;
    cout << "value of foo : " << foo  <<  "\n" << endl;

    ptr = &var;
    cout << "value of ptr : " << ptr << endl;
    cout << "location address of var : " << &var  << endl;
    cout << "dereferenced address of ptr : " << *ptr << "\n" << endl;

    // changing pointing address of ptr
    ptr = &foo;
    cout << "value of ptr : " << ptr  << endl;
    cout << "location address of foo : " << &foo  << endl;
    cout << "dereferenced address of ptr : " << *ptr << "\n" << endl;

    // ---------- REFERENCE ------------
    int& ref = var;
    cout << "value of ref : " << ref << endl;
    cout << "location address of ref : " << &ref  << endl;

     var = 10;
    int var2 = 55;


    return  0;

}

// ------------- b) change in values --------------

// Pointers overriding the content in a variable
int pointersTutorial() {
    int x = 42;
    int *p = &x;

    cout <<"value of x: " <<  x << endl;

    *p = 10;
    cout << "value of x been overridden" << x << endl;
    cout << "memory location of x: " << &x << endl;
    cout << "memory location of p: " << &p << endl;

    cout << "value in p: " << *p << endl;

    return 0;
}

