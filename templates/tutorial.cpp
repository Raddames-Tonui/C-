#include <iostream>
using namespace std;

template <typename T>
class DataBuffer {
private:
    T* data;
    size_t size;
public:
    DataBuffer() : data(nullptr), size(0) {
        cout << "Default constructor called" << endl;
    }

    DataBuffer(size_t s, const T& defaultValue=T()) : size(s) {
        cout << "Parameterized constructor called" << endl;
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = defaultValue;
        }
    }

    DataBuffer (const DataBuffer& other) : size(other.size){
        cout << "Copy constructor called" << endl;
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    DataBuffer& operator=(const DataBuffer& other)  {
        cout << " copy Assignment called " << endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~DataBuffer() {
        delete[] data;
    }

    T& operator[](size_t index) {
        if (index >=size ) {
            cout << "Error: Index " << index << " out of bounds (size = " << size << ")" << endl;
            exit(1);
        }
        return data[index];
    }

    const T& operator[] (size_t index) const {
        if (index >=size ) {
            cout << "Error: Index " << index << " out of bounds (size = " << size << ")" << endl;
            exit(1);
        }
        return data[index];
    }

    [[nodiscard]] size_t getSize() const {
        return size;
    }

    void setAt(size_t index, const T& value) {
        if (index >= size) {
            cout << "Error: Index " << index << " out of bounds (size = " << size << ")" << endl;
            exit(1);
        }
        data[index] = value;
    }

    void printAll() const {
        cout << "[ ";
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << "]" << endl;
    }

    // Resizing if not enough space
    void resize(size_t newSize, const T& defaultValue=T()) {
        delete[] data;
        size = newSize;
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = defaultValue;
        }
    }
};

int main() {

    DataBuffer<int> buffer(3);
    buffer[1] = 38;
    buffer[2] = 99;
    buffer.printAll();


    DataBuffer<string> buffer1;
    buffer1.printAll();
    buffer1.resize(5);
    buffer1[1] = "Raddames";
    buffer1[3] = "Jonah";
    buffer1.setAt(4, "Bob");
    buffer1.printAll();

   auto* ptr = new DataBuffer<string>(3, "");
    ptr->printAll();
    (*ptr)[0] = "hello";
    ptr->setAt(1, "world");
    ptr->printAll();

    DataBuffer<string>& ref = *ptr;
    ref.printAll();
    ref[0] = "world";
    ref.printAll();
    ptr->printAll();  // modified

    DataBuffer<char> buffer2(3, '$');
    buffer2.printAll();
    DataBuffer<char>* ptr3 = &buffer2;
    ptr3->printAll();

    ptr3->setAt(2, 'z');
    ptr3->printAll();
    buffer2.printAll();

    int b = '~';
    cout << b << endl;

    delete ptr;

    return 0;
}