#include <iostream>
#include <exception>
#include <string>

using namespace std;

// ------ CUSTOM EXCEPTION -----------
// Final = cannot be inherited from
class CustomException final : public exception {
    string message;
public:
    explicit CustomException(const string& mess) : message(mess){}

    // 'what()' returns a C-string with the error message
    const char* what() const noexcept override {
    return message.c_str();
    }
};

// ------ BASE ARRAY--------
template<class T>
class Array {
protected:
    T* data;
    int size;
    int capacity;

    void resizeIfFull() {
        if (size >= capacity) {
            int newCap = (capacity == 0) ? 1 : capacity * 2;
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
    explicit Array(int cap = 4) : size(0), capacity(cap) {
        data = new T[capacity];
    }

    virtual void insert(const T& value) = 0;
    virtual T remove() = 0;

    virtual ~Array() {
        delete[] data;
    }

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }

    void print() const {
        cout << "[";
        for (int i = 0; i < size; ++i) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// ------ STACK (LIFO) -------
template<class T>
class Stack : virtual public Array<T> {
public:
    explicit Stack(int cap = 4) : Array<T>(cap) {}

    void insert(const T& value) override {
        this->resizeIfFull();
        this->data[this->size++] = value;
    }

    T remove() override {
        if (this->size <= 0) {
            throw CustomException("Cannot remove from empty stack");
        }
        return this->data[--this->size];
    }
};

// ------ QUEUE (FIFO) -------
template<class T>
class Queue : virtual public Array<T> {
public:
    explicit Queue(int cap = 4) : Array<T>(cap) {}

    void insert(const T& value) override {
        this->resizeIfFull();
        this->data[this->size++] = value;
    }

    T remove() override {
        if (this->size <= 0) {
            throw CustomException("Queue Underflow: Cannot remove from empty queue");
        }
        T front = this->data[0];
        for (int i = 1; i < this->size; ++i) {
            this->data[i - 1] = this->data[i]; // Shift left
        }
        this->size--;
        return front;
    }
};


// ------ DEQUE (Double-ended queue) -------
template<class T>
class Deque : public Stack<T>, public Queue<T> {
public:
    explicit Deque(int cap = 4) : Array<T>(cap), Stack<T>(cap), Queue<T>(cap) {}

    // Push at front
    void insertFront(const T& value) {
        this->resizeIfFull();
        for (int i = this->size; i > 0; --i) {
            this->data[i] = this->data[i - 1];
        }
        this->data[0] = value;
        this->size++;
    }

    // Push at back (default)
    void insert(const T& value) override {
        this->resizeIfFull();
        this->data[this->size++] = value;
    }

    // Remove from front
    T removeFront() {
        return Queue<T>::remove();
    }

    // Remove from back
    T remove() override {
        return Stack<T>::remove();
    }
};

// ------ MAIN TEST -------
int main() {

    Stack<int> myNum;
    myNum.insert(10);
    myNum.insert(2);
    myNum.insert(5);
    myNum.print();

    myNum.remove();
    myNum.print();

    Queue<string>* mystr = new Deque<string>;
    // Deque<string>* mystr = new Deque<string>;
    mystr->insert("Hello");
    mystr->insert("World");
    mystr->insert("Big");
    mystr->insert("World");
    mystr->insert("Small");
    mystr->insert("World");
    mystr->print();

    mystr->remove();
    mystr->print();
    // mystr->removeFront();


    delete mystr;


    // try {
    //     Stack<int> st;
    //     st.insert(10);
    //     st.insert(20);
    //     st.print();
    //     cout << "Popped: " << st.remove() << endl;
    //     cout << "Popped: " << st.remove() << endl;
    //     cout << "Popped: " << st.remove() << endl; // will throw
    // }
    // catch (const CustomException& e) {
    //     cerr << "Custom Exception: " << e.what() << endl;
    // }
    // catch (const exception& e) {
    //     cerr << "Standard Exception: " << e.what() << endl;
    // }
    //
    // return 0;
}
