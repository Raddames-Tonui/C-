#include <iostream>
using namespace std;


// 1. As a sized array
void printSizedArray(int a[10])
{
    for (int i = 0; i < 5; i++)
        a[i] = a[i] + 5;
}

void passArrayAsSizedArray() {
    int a[5] = { 1, 2, 3, 4, 5 };
    printSizedArray(a); // Passing array to function

    // printing array elements
    for (int i = 0; i < 5; i++)
        cout << a[i] << " \n";
}

// 2. As an unsized array

void printUnsizedArray(int a[],int size)
{
    for (int i = 0; i < size; i++)
        a[i] = a[i] + 5;
}

void passArrayAsUnsized() {
    // array creation
    int a[5] = { 1, 2, 3, 4, 5 };
    int n=5;
    printUnsizedArray(a,n); // Passing array to function

    // printing array elements
    for (int i = 0; i < n; i++)
        cout << a[i] << " \n";
}


// 3. As a pointer (pass by pointer)

void printPointerArray(int* a)
{
    for (int i = 0; i < 5; i++)
        *(a + i) = *(a + i) + 5;
}

void passArrayAsPointer() {
    // array creation
    int a[5] = { 1, 2, 3, 4, 5 };
    printPointerArray(a); // Passing array to function
    for (int i = 0; i < 5; i++)
        cout << a[i] << " \n";
}


// 4. As a reference (pass by reference)
void modifyArray(int (&arr)[5])
{
    // deducing size
    int size = sizeof(arr) / sizeof(int);
    for (int i = 0; i < size; ++i) {
        arr[i] *= 2;
    }
}

void passArrayAsReference() {
    int arr[] = { 1, 2, 3, 4, 5 };
    int n = 5;
    modifyArray(arr);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n ";
    }
}
//  ----------------------------------
// Pass Array to Function
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}

void passArray() {
    int arr[10] = {1, 4,2,5,1, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    // passing array
    printArray(arr, n);

}

int main() {
    passArrayAsSizedArray();
    passArrayAsUnsized();
    passArrayAsPointer();
    passArrayAsReference();

}