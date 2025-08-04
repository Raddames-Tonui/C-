#include  <iostream>
using namespace std;


class  Vect {
private:
    int* data;
    int size;

public:
    explicit Vect(int n = 10, int val = 0 ) : size((n)) {
        data = new int[n];
        for (int i = 0; i < n; ++i) {
            data[i] = val;
        }
    }

    // Destructor
    ~Vect() {
        delete[] data;
    };

    // Copy constructor
    Vect(const Vect& obj) {
       size = obj.size;
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = obj.data[i];
        }
    }

    // assignment operator (overloading = operator)
    /**The assignment operator deletes the existing array storage,
         allocates a new array of the proper size,
        and copies elements into this new array.
    */
    Vect& operator=(const Vect& obj) {
        if (this != &obj) {
            delete[] data;

            size = obj.size;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = obj.data[i];
            }
        }
        return *this;   // returning reference Allow chaining  a=b=c
    }

   int getSize() const {
        return size;
    }

    // Index operator
    int& operator[](int index) {
        return data[index];
    }

    // +
    Vect operator+(const Vect& other) const {
        int n = (size < other.size) ? size : other.size;
        Vect result = Vect(n);
        for (int i = 0; i < n; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Vect -
    Vect operator-(const Vect& other) const {
        int n = (size < other.size) ? size : other.size;
        Vect result = Vect(n);
        for (int i = 0; i < n; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Vect *
    int operator*(const Vect& other) const {
        const int n = (size < other.size) ? size : other.size;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += data[i] * other.data[i];
        }
        return sum;
    }

    //==
    bool operator==(const Vect& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // < (Based on Vector magnitude squared)
    bool operator<(const Vect& other) const {
        int selfMag = 0, otherMag = 0;
        int n = (size < other.size) ? size : other.size;
        for (int i = 0; i < size; ++i) {
            selfMag += data[i] * data[i];
            otherMag += other.data[i] * other.data[i];
        }
        return selfMag < otherMag;
    }
    // >
    bool operator>(const Vect& other) const {
        int selfMag = 0, otherMag = 0;
        int n = (size > other.size) ? size : other.size;
        for (int i = 0; i < size; ++i) {
            selfMag += data[i] * data[i];
            otherMag += other.data[i] * other.data[i];
        }
        return selfMag > otherMag;
    }

    // !=
    bool operator!= (const Vect& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& out, const Vect& v);
};

// Output stream operator
ostream& operator<<(ostream& out,  const Vect& v) {
    if (v.data == nullptr || v.size <= 0) {
        out << "[Empty or invalid Vecotr]";
        return out;
    }

    out << "[ ";
    for (int i = 0; i < v.size; ++i) {
        out << v.data[i] << " ";
    }
    out << "]";
    return out;
}


int main() {
    Vect a(5, 3);
    Vect b(3, 2);
    Vect x(2, 6);
    Vect y = x;   // Copy constructor
    Vect z;
    z = x;  // Assignment Operator

    cout << "x" << x << ", y" << y  << ", z" << z << endl;

    // Arithmetic
    Vect c = b - a;
    cout << "Vect c = " << c << endl;

    int d = b * a;
    cout <<  "(b * a) = " << d << endl;

    // Output stream
    cout << "a =" << a << "\n" << "b =" << b << endl;

    // Comparison

    cout << "comparison(==): " << (b == a ? "Yes" : "No") << endl;
    cout << "comparison(<): " << (b < a ? "Yes" : "No") << endl;
}