#include <iostream>
#include <type_traits>
using namespace std;

//  Function Templates
template <typename T>
T add(T a, T b) {
    return a+b;
}


// Class Templates
template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}

    void show() {
        cout <<"Value: " << value << endl;
    }

};

// Template Specialization
template <typename T>
class Printer {
public:
    void print(T value) {
        cout << "Generic: " << value << endl;
    }
};
// Specialize for string
// SFINAE = Substitution Failure Is Not An Error.
// It lets you select code only when types match certain criteria.
template <>
class Printer<string> {
public:
    void print(string value) {
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
    Box<int> b1(100);
    Box<string> b2("Box Template");

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