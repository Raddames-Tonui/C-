#include <iostream>
#include <type_traits>
using namespace std;

//  Function Templates
template <typename T>
T add(T a, T b) {
    return a+b;
}


// Class Templates
// Create a generic class that can store or manipulate any type.
template <typename T>
class Container {
    T value;
public:
    Container(T v) : value(v) {}

    void show() {
        cout <<"Value: " << value << endl;
    }

};

// Template Specialization - Template specialization allows different logic for certain types.
template <typename T>
class Printer {
public:
    void print(T value) {
        cout << "Generic: " << value << endl;
    }
};

template <>
class Printer<string> {
public:
    void print(const string &value) {
        cout << "String value: " << value << endl;
    }
};





// std::enable_if and SFINAE
template <typename T>
enable_if_t<is_integral_v<T>, void>
printType(T val) {
    cout << "Integer: "<< val << endl;
}

template <typename T>
enable_if_t<is_floating_point_v<T>, void>
printType(T val) {
    cout << "Floating point: " << val << endl;
}


int main () {
    cout << add<int>(2, 3) << endl;
    cout << add<double> (1.244, 32.5) << endl;
    cout << add<string>("Hi ", "there!") << endl;


    cout << "------  Class Templates ------" << endl;
    Container<int> b1(100);
    Container<string> b2("Container Template");

    b1.show();
    b2.show();

    cout << "------Template Specialization ------" << endl;
    Printer<int> p1;
    p1.print(45);
    p1.print('a');

    Printer<string> p2;
    p2.print("This is templates");

    cout << "------std::enable_if and SFINAE ------" << endl;
    printType(10);
    printType(3.143);

    return 0;
}





















