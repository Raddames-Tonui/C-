## Operator Overloading in C++

Operator overloading in C++ lets you redefine the way operators work for user-defined types (e.g., classes). It improves code readability and mimics the behavior of built-in types.

---

## 🧠 Concept Overview

In C++, you can **overload most operators** (like `+`, `-`, `==`, `[]`, `()`, etc.) to work with your own classes. You're essentially **defining a function** that describes what should happen when that operator is used.

---

## 📌 Where to Add Operator Overloads

1. **Inside the class (as member function)**
   Best for operators that:

    * Need access to private members.
    * Must act on the class instance itself (e.g., assignment `=`, `[]`, `()`).

2. **Outside the class (as friend or global function)**
   Best for:

    * Operators where the **left-hand operand isn't the object itself**.
    * Symmetric binary operators like `+`, `==`.

---

## 📦 Syntax Overview

### 👉 Member Function Overload

```cpp
class Vector {
    int x;
public:
    Vector(int val) : x(val) {}
    Vector operator+(const Vector& v) const {
        return Vector(this->x + v.x);
    }
};
```

### 👉 Non-Member (Friend) Function

```cpp
class Vector {
    int x;
public:
    Vector(int val) : x(val) {}
    friend Vector operator+(const Vector& v1, const Vector& v2);
};

Vector operator+(const Vector& v1, const Vector& v2) {
    return Vector(v1.x + v2.x);
}
```

---

## 🛠️ Operators You Can Overload

| Category            | Operators                            |                           |         |
| ------------------- | ------------------------------------ | ------------------------- | ------- |
| Arithmetic          | `+`, `-`, `*`, `/`, `%`              |                           |         |
| Assignment          | `=`, `+=`, `-=`, `*=`, `/=`, `%=`    |                           |         |
| Comparison          | `==`, `!=`, `<`, `>`, `<=`, `>=`     |                           |         |
| Logical             | `&&`, \`                             |                           | `, `!\` |
| Bitwise             | `&`, \`                              | `, `^`, `\~`, `<<`, `>>\` |         |
| Increment/Decrement | `++`, `--`                           |                           |         |
| Subscript           | `[]`                                 |                           |         |
| Function call       | `()`                                 |                           |         |
| Dereference         | `*`, `->`, `->*`                     |                           |         |
| Memory management   | `new`, `delete`, `new[]`, `delete[]` |                           |         |

🔴 **Cannot be overloaded:**
`::` (scope resolution), `.*`, `sizeof`, `typeid`, `?:`, `const_cast`, `static_cast`, `reinterpret_cast`, `dynamic_cast`.

---

## 📘 Best Practices

* **Return by value** for arithmetic-style operators (`+`, `-`, `*`).
* **Return by reference** for assignment-style operators (`=`, `+=`).
* **Mark as `const`** if the function doesn’t modify the object.
* Be cautious when overloading logical operators: they don’t short-circuit.

