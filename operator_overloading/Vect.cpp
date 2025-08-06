#include  <iostream>
using namespace std;


class  Vect {
private:
    int* data;
    int size;

public:
    Vect(int n = 10, int val = 0 ) : size((n)) {
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

    int getSize() const {
        return size;
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

    // Index operator
    int& operator[](int index) {
        if (index < 0 || index >= size)
            cout << "index out of bounds" << endl;
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

    //  -
    Vect operator-(const Vect& other) const {
        int n = (size < other.size) ? size : other.size;
        Vect result = Vect(n);
        for (int i = 0; i < n; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // negate -
    Vect operator-() const {
        Vect result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = -data[i];
        }
        return result;
    }

    // *
    int operator*(const Vect& other) const {
        const int n = (size < other.size) ? size : other.size;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += data[i] * other.data[i];
        }
        return sum;
    }

    // ^
    int operator^(const Vect& other) const {
        int n = (size < other.size) ? size : other.size;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    //== only checks value equality, not obj identity
    bool operator==(const Vect& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // !=
    bool operator!= (const Vect& other) const {
        return !(*this == other);  // Code reuse ==
    }

    // < (Based on Vector magnitude squared)
    bool operator<(const Vect& other) const {
        int n = (size < other.size) ? size : other.size;

        for (int i = 0; i < n; ++i) {
            if (data[i] < other.data[i]) return true;
            if (data[i] > other.data[i]) return false;
        }

        return size < other.size;
    }

    // >
    bool operator>(const Vect& other) const {
        int n = (size < other.size) ? size : other.size;

        for (int i = 0; i < n; ++i) {
            if (data[i] > other.data[i]) return true;
            if (data[i] < other.data[i]) return false;
        }

        return size > other.size;
    }

    // >=
    bool operator>= (const Vect& other) const {
        int n = (size < other.size) ? size : other.size;

        for (int i = 0; i < n; ++i) {
            if (data[i] > other.data[i]) return true;
            if (data[i] < other.data[i]) return false;
        }
        return size >= other.size;
    }

    // <=
    bool operator<=(const Vect& other) const {
        return !(other < *this);
    }
    // +=
    Vect& operator+=(const Vect& other) {
        if (size != other.size) {
            cout << "Size mismatch in += operator";
        }
        for (int i = 0; i < size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    // -=
    Vect& operator-=(const Vect& other) {
        if (size != other.size) {
            cout << "Size mismatch in -= operator";
        }
        for (int i = 0; i < size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    // Increment and Decrement
    // Prefix ++v
    Vect& operator++() {
        for (int i = 0; i < size; ++i) {
            ++data[i];
        }
        return *this;
    }

    // Postfix v++
    Vect operator++(int) {
        Vect temp = *this;     // copy current state
        ++(*this);                // use prefix
        return temp;
    }

    // Prefix --v
    Vect& operator--() {
        for (int i = 0; i < size; ++i) {
            --data[i];
        }
        return *this;
    }

    // Postfix v--
    Vect operator--(int) {
        Vect temp = *this;
        --(*this);
        return temp;
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
    Vect x(2, 5);
    Vect y = x;   // Copy constructor
    Vect z;
    z = x;  // Assignment Operator

    cout << "x" << x << ", y" << y  << ", z" << z << endl;

    // Negate
    Vect negated = -z;
    cout << "Negated: " << negated << endl;

    // Arithmetic
    Vect c = b + a;
    cout << "Vect c = " << c << endl;

    int d = b * a;
    cout <<  "(b * a) = " << d << endl;



    // Output stream
    cout << "output stream a =" << a << "\n" << "output stream b =" << b << endl;

    // Comparison
    cout << "comparison(==): " << (y != z ? "Yes" : "No") << endl;
    cout << "comparison(<): " << (b > a ? "Yes" : "No") << endl;

    // Increment and decrement
    Vect inc(5);
    inc[0] = 2; inc[1] = 6; inc[2]= 5; inc[3]=0; inc[4] = 8;
    Vect dec(5);
    dec[0] = 2; dec[1] = 6; dec[2]= 5; dec[3]=0; dec[4] = 8;

    cout << "++inc: " << ++inc << endl;  //  pre-increment: increment, then return result
    cout << "inc++ : " << inc++ << endl;

    cout << "Before --inc: " << dec << endl;
    cout << "--inc: " << --dec << endl;  // Shows value after decrement	Immediately

    cout << "inc-- : " << dec-- << endl;
    cout << "After inc--: " << dec << endl;  // Shows value before decrement Change happens after




}