## 🧠 Core Concept: Operator Overloading

**Definition**: Operator overloading is the process of providing a special meaning to an operator for a user-defined type.

C++ lets you overload **almost** all operators except:

* `::` (scope resolution)
* `.` (member access)
* `.*` (pointer-to-member access)
* `sizeof`, `typeid`, `alignof`

You can overload operators **as member functions** or **non-member (friend) functions** depending on the use case.

---

## 🧩 Syntax Overview

### 🔹 Member function:

```cpp
class MyClass {
public:
    MyClass operator+(const MyClass& other); // member
};
```

### 🔹 Friend / non-member function:

```cpp
class MyClass {
    friend MyClass operator+(const MyClass& lhs, const MyClass& rhs);
};
```

---

## 🚀 Example 1: Overloading `+` for a `Vector` class (with pointer & reference concepts)

### ✅ Use case:

You want to add two vectors with syntax like: `v1 + v2`

```cpp
#include <iostream>
using namespace std;

class Vector {
private:
    int* data; // dynamic array
    int size;

public:
    Vector(int sz) : size(sz) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = 0;
    }

    Vector(const Vector& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    ~Vector() {
        delete[] data;
    }

    void set(int index, int value) {
        if (index >= 0 && index < size)
            data[index] = value;
    }

    void print() const {
        for (int i = 0; i < size; ++i)
            cout << data[i] << " ";
        cout << endl;
    }

    Vector operator+(const Vector& rhs) const {
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result.data[i] = this->data[i] + rhs.data[i];
        return result;
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
```

### 💡 Concepts used:

* **Pointers**: `int* data` stores dynamic memory.
* **References**: Parameters like `const Vector& rhs`.
* **Copy constructor** ensures deep copy.
* **Destructor** cleans up.

---

## 🔥 Example 2: Overloading `[]` and assignment operator (`=`)

```cpp
#include <iostream>
using namespace std;

class Array {
private:
    int* arr;
    int size;

public:
    Array(int size) : size(size) {
        arr = new int[size];
        for (int i = 0; i < size; i++)
            arr[i] = 0;
    }

    ~Array() {
        delete[] arr;
    }

    int& operator[](int index) {
        if (index >= 0 && index < size)
            return arr[index];
        throw out_of_range("Index out of bounds");
    }

    const int& operator[](int index) const {
        if (index >= 0 && index < size)
            return arr[index];
        throw out_of_range("Index out of bounds");
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            arr = new int[size];
            for (int i = 0; i < size; ++i)
                arr[i] = other.arr[i];
        }
        return *this;
    }

    void display() {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    Array a1(5);
    a1[2] = 10;
    a1.display();

    Array a2(5);
    a2 = a1;
    a2[2] = 99;

    a1.display();
    a2.display();
    return 0;
}
```

### 💡 Concepts:

* `operator[]` returns a **reference**
* Deep copying avoids memory leaks.
* Self-assignment check: `if (this != &other)`

---

## 🧪 Example 3: Overloading `*` (pointer dereference) to mimic smart pointer

```cpp
#include <iostream>
using namespace std;

class IntWrapper {
private:
    int* ptr;

public:
    IntWrapper(int val) {
        ptr = new int(val);
    }

    ~IntWrapper() {
        delete ptr;
    }

    int& operator*() {
        return *ptr;
    }

    int* operator->() {
        return ptr;
    }
};

int main() {
    IntWrapper num(42);
    cout << *num << endl;

    *num = 100;
    cout << *num << endl;
    return 0;
}
```

---

## 🔄 Commonly Overloaded Operators & Use-Cases

| Operator           | Use-case            | Tip                           |
| ------------------ | ------------------- | ----------------------------- |
| `+`, `-`, `*`, `/` | Math operations     | Use as member or friend       |
| `[]`               | Indexing into class | Return reference              |
| `()`               | Functor objects     | Often used in DSLs            |
| `==`, `!=`         | Comparisons         | Define both if you define one |
| `<<`, `>>`         | Stream input/output | Use as friend function        |
| `=`                | Assignment          | Always handle self-assignment |
| `->`, `*`          | Smart pointers      | Used in wrapper classes       |

---

## 💥 Pro Tips

* Use `const` correctness on methods and parameters.
* For symmetric binary operators like `+`, prefer friend functions.
* Always implement **rule of 3/5/0** (copy constructor, assignment operator, destructor).
* Use **move semantics** when performance matters.

---

## 📌 Final Thought

Operator overloading brings elegance to your class interfaces but must be **used wisely**. Misuse leads to confusing code. Always ensure that overloaded behavior is **intuitive** and matches the semantics of the operator.


