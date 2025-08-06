// References
// Pointers provide one way to refer indirectly to an object.
// Another way is through references.
// A reference is simply an alternative name for an object.


/**
* References are most often used for passing function arguments and are also often
used for returning results from functions.
 */
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

int main() {
    string author = "Samuel Clemens";
    string& penName = author;

    cout << penName << endl;

    penName = "John";
    cout << penName << endl;
    cout << author<< endl;
}
