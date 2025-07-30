#include <iostream>
using namespace std;

class Shape {
public:
    virtual ~Shape() {
        cout << "Shape destroyed \n ";
    }
};

class Circle : public Shape {
private:
    int* data{};
public:
    Circle() {
        data = new int[10];
        cout << "Circle created \n ";
    }


    ~Circle() override {
        cout << "Circle destroyed \n ";
    }
};

int main() {

    const Shape* ptr = new Circle();  // base pointer to derived object

    delete ptr;
    ptr = nullptr;

    return 0;
}

// What happens on delete ptr;
// Since Shape has a virtual destructor:
    // 1. Compiler sees delete ptr;
    // 2. Follows the vptr (virtual table pointer)
    // 3. Finds the correct destructor, which is:
            // Circle::~Circle() — this runs first
            // then Shape::~Shape() — this runs next

// ┌─────────────┐       ┌──────────────────────────┐
// obj --> │   [vptr]    │ ----> │ vtable → Derived::~Derived │
// │ Base part   │       │        → Base::~Base      │
// │ Derived part│       └──────────────────────────┘
// └─────────────┘
//
// delete obj;  // Follows vtable, calls destructors in order


// | Scenario                   | Destructor Called        | Memory Leaks? |
// | -------------------------- | ------------------------ | ------------- |
// | `virtual ~Shape()` present | `~Circle()` + `~Shape()` | ❌ No          |
// | `~Shape()` not virtual     | `~Shape()` only          | ✅ Yes         |
