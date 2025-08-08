#include <iostream>

using namespace std;

template <typename T>
class Vector {
private:
    T* data = nullptr;
    int size;
    int capacity;

    void resize_if_full() {
        if (size >= capacity) {
            const int newCap = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCap];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCap;
        }
    }

public:
    // Default constructor
    explicit Vector(const int cap = 10) : size(0), capacity(cap){
        data = new T[cap];
    }

    // Initializer list constructor
    Vector(initializer_list<T> list)
        : size(list.size()), capacity(list.size())
    {
        data = new T[capacity];
        int i = 0;
        for (const T& val : list) {
            data[i++] = val;
        }
    }

    // copy const
    Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            // data[i] = other.data[i];
            *(data + i) = other.data[i];
        }
    }

    // copy assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Vector () {
        delete[] data;
        data = nullptr;
    }

    // Add an element
    void push_back(const T& value) {
        resize_if_full();
        data[size++] = value;
    }
    // Remove last element
    void pop_back() {
        if (size == 0)
            cout << "Vector is empty" << endl;
        size--;
    }
    // Insert at position
    void insert(int pos, const T& value ) {
        if (pos < 0 || pos > size)
            cout << "Index out of bounds" << endl;
        resize_if_full();
        for (int i = size; i > pos; i--) {
            data[i] = data[i - 1];
        }
        data[pos] = value;
        size++;
    }
    // Delete 1 element
    void erase(int pos) {
        if (pos < 0 || pos >= size) {
            cout << "Invalid delete position" << endl;
        }
        for (int i = pos; i < size -1; i++){
            data[i] = data[i + 1];
        }
        size--;
    }

    // Erase range [start, end]
    void erase(int start, int end) {
        if (start < 0 || end > size || start >=end) {
            cout << "Invalid erase position" << endl;
        }
        int range = end - start;
        for (int i = start; i < + range < size; i++) {
            data[i] = data[i + range];
        }
        size -= range;
    }

    // get an element
    T& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }else {
            throw out_of_range("Index out of range");
        }
    }
    // get size
    [[nodiscard]] int getSize() const{
        return size;
    }

    // clear
    void clear() {

    }

    // print all elements
    void print() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i != size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

};

// Functions demonstrating pass by value, pointer, reference
template<typename T>
void printByValue(const Vector<T>& vec) {
    cout << "Pass by Value: ";
    vec.print(); // copies
}

template<typename T>
void printByPointer(Vector<T>* vec) {
    cout << "Pass by Pointer: ";
    vec->print();
}

template<typename T>
void printByReference(Vector<T>& vec) {
    cout << "Pass by Reference: ";
    vec.print();  // uses original
}

int main () {
    Vector<int> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.print();
    // vec1.getSize(); // result ignored Because it was called it but did nothing with the result
    cout << vec1.getSize() << endl;

    printByValue(vec1);
    printByReference(vec1);
    printByPointer(&vec1);

    auto* ptr1 = new Vector<string>(2);
    ptr1->push_back("henry");
    ptr1->push_back("Gilbert");
    ptr1->push_back("jacky");
    ptr1->print();
    cout << ptr1->getSize() << endl;

    Vector<string> vec2 = {"dog", "cat", "elephant", "monkey", "cow"};
    Vector<string>* ptr3 = &vec2;
    Vector<string>& ref2 = vec2;
    ref2.erase(2);
    ptr3->print();
    ref2.print();
    vec2.print();
    ptr3->erase(0);
    ptr3->print();
    vec2.print();
    delete ptr1;

    return 0;
}