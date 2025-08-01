#include <iostream>
using namespace std;

class Vector {
private:
    int* data; // dynamic array
    int size;

public:
    // Initializer List: : size(sz)
    Vector(int sz) : size(sz) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = 0;
    }

    // Copy constructor
    Vector(const Vector& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    ~Vector() {
        delete[] data;
    }

    // Set value at index
    void set(int index, int value) {
        if (index >= 0 && index < size)
            data[index] = value;
    }

    // Print values
    void print() const {
        for (int i = 0; i < size; ++i)
            cout << data[i] << " ";
        cout << endl;
    }

    // Overload + operator
    Vector operator+(const Vector& rhs) const {
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result.data[i] = this->data[i] + rhs.data[i];
        return result; // Copy elision will optimize this
    }
};

int main() {
    Vector v1(3), v2(3);
    v1.set(0, 1); v1.set(1, 2); v1.set(2, 3);
    v2.set(0, 4); v2.set(1, 5); v2.set(2, 6);

    Vector v3 = v1 + v2;
    v3.print();
    return 0;
}
