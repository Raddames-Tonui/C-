#include <iostream>
using namespace std;

class Student {
private:
    int age;
    float marks;

public:
    // Default constructor
    Student() {
        age = 0;
        marks = 0.0;
    }

    // Parameterized constructor
    Student(int a, float m) {
        age = a;
        marks = m;
    }

    // Copy constructor:
    // special constructor in C++ used to create a new object as a copy of an existing object.
    Student(const Student& other) {
        age = other.age;
        marks = other.marks;
    }

    // Destructor
    ~Student() {
        cout << endl;
    }

    void display() const {
        cout << "Age: " << age << ", Marks: " << marks << endl;
    }

    void setAge(int a) { age = a; }
    void setMarks(float m) { marks = m; }

    int getAge() const { return age; }
    float getMarks() const { return marks; }
};

// Pass by Value (creates a copy)
void passByValue(Student s) {
    cout << "[By Value] ";
    s.display();
}

// Pass by Reference (no copy, can modify)
void passByReference(Student& s) {
    cout << "[By Reference] ";
    s.display();

    // Modify via setters
    s.setAge(s.getAge() + 1);
    s.setMarks(s.getMarks() + 1.0);

    s.display();
}

// Pass by const Reference (no copy, safe)
void passByConstRef(const Student& s) {
    cout << "[By Const Ref] ";
    s.display();

    // s.setAge(30); // Error: modifying not allowed on const reference
}

// Pass by Pointer
void passByPointer(Student* s) {
    cout << "[By Pointer] " << s;
    s->display();

    // Modify via setters
    s->setAge(s->getAge() + 5);
    s->setMarks(s->getMarks() + 3.0);

    s->display();
}

// Pass by const Pointer
void passByConstPointer(const Student* s) {
    cout << "[By Const Pointer] ";
    s->display();

    // s->setAge(50); // Not allowed, pointer is const
}

// Rvalue Reference (&&) — usually used for temporary objects or move semantics
void passByRvalueRef(Student&& s) {
    cout << "[By Rvalue Ref] ";
    s.display();
}

// ------------ CHAR -----------------
void printCharArray(const char* str) {
    cout << "[printCharArray] " << str << endl;
}

void modifyCharArray(char* str) {
    str[0] = 'B';  // Change first letter Changes 'R' -> 'B'
}


void charHandler() {
    char name[] = "Raddames";  // mutable array on stack
    char* literal = (char*)"Raddames";  // Points to a string literal,  usually stored in read-only memory
    cout << literal[0] << endl;


    printCharArray(name);
    modifyCharArray(name);
    printCharArray(name);

}

int main() {
    charHandler();

    // Student s1(18, 80.0);
    // Student s2(20, 85.0);
    //
    // passByValue(s1);         // Copy
    // passByReference(s1);     // Modifies s1
    // passByConstRef(s2);      // Safe read-only
    // passByPointer(&s2);      // Modifies s2
    // passByConstPointer(&s2); // Read-only
    // passByRvalueRef(Student(25, 99.0)); // Temporary object
    //
    // cout << "--- After modifying ---\n";
    // s1.display();
    // s2.display();

    return 0;
}
