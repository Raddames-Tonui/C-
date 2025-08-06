**C++ Inheritance: Everything You Need to Know**

---

### 1. **What is Inheritance?**

Inheritance allows a class (called a **derived** or **child** class) to acquire properties and behaviors (data and functions) from another class (called a **base** or **parent** class).

```cpp
class Base {
public:
    void show() {
        cout << "Base class";
    }
};

class Derived : public Base {
    // inherits show()
};
```

### 2. **Syntax**

```cpp
class Derived : access_specifier Base {
    // members of derived class
};
```

* `access_specifier` can be `public`, `protected`, or `private`.

### 3. **Types of Inheritance**

* **Single Inheritance**: One base, one derived.
* **Multilevel Inheritance**: Derived from a derived.
* **Multiple Inheritance**: One derived from multiple bases.
* **Hierarchical Inheritance**: Multiple derived from one base.
* **Hybrid Inheritance**: Combination of any of the above.

### 4. **Access Specifiers**

| Base class | Inherited as public | Inherited as protected | Inherited as private |
| ---------- | ------------------- | ---------------------- | -------------------- |
| public     | public              | protected              | private              |
| protected  | protected           | protected              | private              |
| private    | not inherited       | not inherited          | not inherited        |

### 5. **Function Overriding**

A derived class can override base class methods.

```cpp
class Base {
public:
    void greet() {
        cout << "Hello from Base";
    }
};
class Derived : public Base {
public:
    void greet() {
        cout << "Hello from Derived";
    }
};
```

### 6. **Using `::` Scope Resolution**

To call base class version explicitly:

```cpp
derivedObj.Base::greet();
```

### 7. **Constructors and Destructors**

* Base constructor runs **before** derived.
* Derived destructor runs **before** base.

### 8. **Virtual Functions and Polymorphism**

```cpp
class Base {
public:
    virtual void show() {
        cout << "Base";
    }
};
class Derived : public Base {
public:
    void show() override {
        cout << "Derived";
    }
};
```

### 9. **Abstract Classes**

A class with at least one pure virtual function is abstract.

```cpp
class Abstract {
public:
    virtual void show() = 0; // pure virtual
};
```

### 10. **`protected` keyword**

* Allows access in derived class, but not outside the class hierarchy.

### 11. **Order of Construction & Destruction**

* Construction: Base -> Derived
* Destruction: Derived -> Base

### 12. **Ambiguity in Multiple Inheritance**

Use scope resolution to resolve ambiguity.

```cpp
class A { public: void print() { cout << "A"; } };
class B { public: void print() { cout << "B"; } };
class C : public A, public B {
public:
    void call() {
        A::print();  // Resolves ambiguity
    }
};
```

### 13. **Virtual Base Classes**

Avoids duplication when using multiple inheritance.

```cpp
class A {
public:
    int x;
};
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {
    // Only one A is inherited
};
```

### 14. **Best Practices**

* Prefer `public` inheritance for "is-a" relationships.
* Use `virtual` functions for polymorphism.
* Avoid multiple inheritance unless necessary.
* Make destructors `virtual` if base is meant to be inherited.

```cpp
class Base {
public:
    virtual ~Base() {}  // Important!
};
```

---

This guide gives a compact but thorough overview of C++ inheritance—sufficient for practical use and deeper learning.
