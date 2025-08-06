#include <iostream>
#include <string>
using namespace std;

// Abstract base class using a pure virtual function
class Printable {
public:
    virtual void print() const = 0; // pure virtual function
    virtual ~Printable() {}
};

// Base class
class Person : public Printable {
protected:
    string name;
    int age;

public:
    static int count; // static member to count Person objects

    // Default constructor
    Person() : name("Unknown"), age(0) {
        ++count;
        cout << "Person default constructor called.\n";
    }

    // Parameterized constructor
    Person(string name, int age) : name(name), age(age) {
        ++count;
        cout << "Person parameterized constructor called.\n";
    }

    // Copy constructor
    Person(const Person& other) : name(other.name), age(other.age) {
        ++count;
        cout << "Person copy constructor called.\n";
    }

    // Copy assignment operator
    Person& operator=(const Person& other) {
        cout << "Person copy assignment called.\n";
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        return *this;
    }

    // Destructor
    virtual ~Person() {
        --count;
        cout << "Person destructor called.\n";
    }

    // Friend class
    friend class Doctor;

    // Overriding pure virtual function
    void print() const override {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// Initialize static member
int Person::count = 0;

// Derived class 1
class Student : virtual public Person {
protected:
    string university;

public:
    Student(string name, int age, string university)
        : Person(name, age), university(university) {
        cout << "Student constructor called.\n";
    }

    void print() const override {
        Person::print();
        cout << "University: " << university << endl;
    }
};

// Derived class 2
class Employee : virtual public Person {
protected:
    string company;

public:
    Employee(string name, int age, string company)
        : Person(name, age), company(company) {
        cout << "Employee constructor called.\n";
    }

    void print() const override {
        Person::print();
        cout << "Company: " << company << endl;
    }
};

// Diamond inheritance
class WorkingStudent : public Student, public Employee {
private:
    double salary;

public:
    WorkingStudent(string name, int age, string university, string company, double salary)
        : Person(name, age), Student(name, age, university), Employee(name, age, company), salary(salary) {
        cout << "WorkingStudent constructor called.\n";
    }

    void print() const override {
        Person::print(); // only one Person subobject due to virtual inheritance
        cout << "University: " << university << ", Company: " << company
             << ", Salary: " << salary << endl;
    }
};

// Friend class
class Doctor {
public:
    void diagnose(const Person& p) {
        // Accessing protected member using friend privilege
        cout << "Doctor diagnosing: " << p.name << " who is " << p.age << " years old.\n";
    }
};

// Raw pointer function
void printPersonViaPointer(Person* ptr) {
    cout << "Printing via pointer: ";
    ptr->print();
}

// Reference function
void printPersonViaReference(const Person& ref) {
    cout << "Printing via reference: ";
    ref.print();
}

// Pass by value (uses copy constructor)
void printPersonByValue(Person p) {
    cout << "Printing by value (copy): ";
    p.print();
}

int main() {
    cout << "=== Creating base Person ===" << endl;
    Person p1("Alice", 30);
    p1.print();

    cout << "\n=== Copying Person ===" << endl;
    Person p2 = p1; // copy constructor
    p2.print();

    cout << "\n=== Assignment ===" << endl;
    Person p3;
    p3 = p1; // copy assignment
    p3.print();

    cout << "\n=== Using Friend Class ===" << endl;
    Doctor d;
    d.diagnose(p1);

    cout << "\n=== Creating WorkingStudent (Diamond Inheritance) ===" << endl;
    WorkingStudent ws("Bob", 22, "MIT", "Google", 1500.0);
    ws.print();

    cout << "\n=== Function Calls with Different Passing Techniques ===" << endl;
    printPersonByValue(p1);
    printPersonViaReference(p1);
    printPersonViaPointer(&p1);

    cout << "\nTotal Person objects created: " << Person::count << endl;

    return 0;
}
