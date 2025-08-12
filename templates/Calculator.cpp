#include <iostream>
using namespace std;

template <typename T1, typename T2>
class Calculator {
    T1 a;
    T2 b;

public:
    Calculator(T1 x, T2 y) : a(x), b(y) {}

    double add() const {
        return static_cast<double>(a) + static_cast<double>(b);
    }

    double subtract() const {
        return static_cast<double>(a) - static_cast<double>(b);
    }

    double multiply() const {
        return static_cast<double>(a) * static_cast<double>(b);
    }

    double divide() const {
        if (b == 0) {
            cerr << "Error: Division by zero!\n";
            return 0;
        }
        return static_cast<double>(a) / static_cast<double>(b);
    }
};

int main() {
    auto x = 2;
    auto y = 3.4;

    Calculator<int,double> calc1 (x,y);
    Calculator<float, int> calc2(7.5f, 3);


    cout << "Calc1 Add: " << calc1.add() << endl;
    cout << "Calc1 Subtract: " << calc1.subtract() << endl;
    cout << "Calc1 Multiply: " << calc1.multiply() << endl;
    cout << "Calc1 Divide: " << calc1.divide() << endl;

    cout << "\nCalc2 Add: " << calc2.add() << endl;
    cout << "Calc2 Subtract: " << calc2.subtract() << endl;
    cout << "Calc2 Multiply: " << calc2.multiply() << endl;
    cout << "Calc2 Divide: " << calc2.divide() << endl;

    return 0;
}
