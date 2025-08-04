
#include <iostream>

using namespace std;

using std::string;

class Passenger {
private:
    int age;

public:
    Passenger() {
        age = 0;
    }

    void setAge(int age) {
        this->age = age;
    }

    int getAge() {
        return age;
    }
};

int main () {

    char ch = 'Q';
    char* ptr = &ch;
    cout << "ch value: " << *ptr << endl;

    ch = 'p';
    cout << "new value: " << *ptr << endl;

    *ptr = 'Y';
    cout << "new value: " << *ptr << endl;

    // Arrays and Pointers
    char c[] = {'q', 'r', 'a'};
    char* p = c;
    char* q = &c[0]; // Point to memory address of c
    cout << *p << *q << c[0] << endl;
    cout << c[11] << endl;  // Accessing out-of-bounds memory

    string s = "hello";
    string t = "not" + s;
    // cout << t << endl;

    // POINTERS,  creating new memory address in the Heap
    Passenger* p1 = nullptr;
    p1 = new Passenger;
    delete p1;
    p1 = nullptr; // Sets pointer to null to avoid dangling

    auto* p2 = new Passenger;  // Points to a new Passenger
    p2->setAge(20); // Pointers use -> or (*p2).setAge() to call functions
    cout << "p2: " << p2->getAge() << endl;

    Passenger* p3 = p2;
    cout << "P3: "<<p3->getAge() << endl;

    delete p2; // destroys the object p2 points to
    // delete p3;  //  Heap corruption detected, usually caused by double deletion,
                    // invalid memory access, or out-of-bounds writes.
    p2 = nullptr;
    p3 = nullptr;



    char* buffer = new char[6](); // Initializes all 30 chars to '\0'
    buffer[3] = 'A';
    cout << buffer[3] << endl;

    delete[] buffer;
    buffer = nullptr;

    return 0;

}
