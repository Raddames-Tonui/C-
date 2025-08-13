#include <iostream>
#include <vector>

using namespace std;

/**
 * C++11 introduced lambda expressions to allow inline functions
 * which can be used for short snippets of code that are not going
 * to be reused. Therefore, they do not require a name.
 * They are mostly used in STL algorithms as callback functions.
 *
 * Lambda syntax:
 * [capture-clause] (parameters) -> return-type { body }
 *
 * Capture Clause:
 * [&]        : capture all external variables by reference.
 * [=]        : capture all external variables by value.
 * [a, &b]    : capture 'a' by value and 'b' by reference.
 * []         : capture nothing; can only use local variables.
 */

void print(const vector<int>& v) { // pass by const ref to avoid copy
    for (auto x : v) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {

    // Simple lambda example
    auto lambda = [](int x) { return x + x; };
    cout << "lambda: " << lambda(2) << endl; // prints 4

    vector<int> v1, v2;

    // Capture v1 and v2 by reference
    auto byRef = [&](int m) {
        v1.push_back(m);
        v2.push_back(m);
    };
    // Effect: modifies outer vectors directly

    // Capture v1 and v2 by value
    auto byVal = [=](int m) {
        // v1.push_back(m); // ERROR: cannot modify captured by value
        // v2.push_back(m); // ERROR
    };
    // Effect: does NOT modify outer vectors; push_back is invalid

    // Capture v1 and v2 explicitly by reference
    auto mixed = [&v1, &v2](int m) {
        v1.push_back(m);
        v2.push_back(m);
    };
    // Same effect as byRef

    // Capture everything by value, except v2 by reference
    auto mixed2 = [=, &v2](int m) {
        // v1.push_back(m); // cannot modify v1 (captured by value)
        v2.push_back(m);
    };
    // Effect: modifies only v2, v1 remains unchanged

    // Push values into vectors
    byRef(10);     // adds 10 to both v1 and v2
    byVal(20);     // does nothing
    mixed2(30);    // adds 30 only to v2

    // Print vectors to see results
    cout << "v1: "; print(v1); // expected: 10
    cout << "v2: "; print(v2); // expected: 10 30


    int x = 10;

    // -------Lambda capturing a Value -------------
    // Original doesn't change
    auto lambdaval = [=] (int x) {
        cout << "By Value: " << x +2 << endl;
    };
    lambdaval(x);
    cout << "Original: "<< x << endl;

    // -------Lambda capturing a pointer -------------
    // Changes original value
    int *ptr = &x;

    auto lambdaPtr= [ptr]() {
        cout << "Value via pointer: " << *ptr << endl;
    };
    lambdaPtr();  // prints 10

    *ptr = 20; // modify original value
    lambdaPtr();  // prints 20

    // -------Capturing pointer by reference----------
    // Using [&ptr] lets you modify the pointer itself inside the lambda:
    auto lambdaRef = [&ptr]() {
        *ptr += 5;
    };
    lambdaRef(); // prints 25
    cout << "pointer by reference: " << *ptr << endl; // modifies the original pointer's pointee

    int y = 100;

    // mutable makes the lambda’s operator() non-const.
    auto changePtr = [ptr, y]() mutable {
        ptr = &y;
    };
    changePtr();
    cout << "[ptr, y]: "<< *ptr << endl; // prints 25

    auto changePtrByRef = [&ptr, y]() mutable {
        ptr = &y;
    };
    changePtrByRef();
    cout << "[&ptr, y]: "<< *ptr << endl; // now prints 100


    return 0;
}

/**
 * Applications:
 * 1. Inline, Anonymous Functions: Small functions directly where needed.
 * 2. STL Algorithms: Custom comparison or transformation logic.
 * 3. Callbacks / Event Handling: For async operations or events.
 * 4. Threading / Concurrency: Pass quick inline tasks to threads.
 * 5. Custom Comparators in Containers: e.g., priority_queue, set.
 */
