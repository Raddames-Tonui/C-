# Rule of Three and Rule of Five in C++

## 📑 Table of Contents

* [Copy Constructor](#1-copy-constructor)
* [Destructor](#2-destructor-rule-of-5)
* [Copy Assignment Operator](#3-copy-assignment-operator-rule-of-5)
* [Move Constructor](#4-move-constructor-rule-of-5)
* [Move Assignment Operator](#5-move-assignment-operator-rule-of-5)

In C++, when a class manages resources like dynamic memory, file handles, or sockets, you must define certain special member functions to ensure proper resource management. This practice is known as the **Rule of Three**, or more comprehensively, the **Rule of Five**.

## 🔺 Rule of Three

If a class needs any one of the following, it almost certainly needs all three:

| Component Purpose                  | Purpose                                  |
| ---------------------------------- | ---------------------------------------- |
| **1. 🧹 Destructor**               | Releases the resource (e.g., `delete[]`) |
| **2. 🧬 Copy Constructor**         | Creates a deep copy when copying         |
| **3. 📝 Copy Assignment Operator** | Handles assigning one object to another  |

Why? Because if you define one (e.g., destructor to clean up memory), you need to define the others to ensure deep copying and safe ownership.

## 🔹 Rule of Five (C++11 and beyond)

With move semantics introduced in C++11, if your class manages resources, you should consider defining all of these:

| **Component Purpose**               | **Purpose**                                           |
|-------------------------------------| ----------------------------------------------------- |
| **4.  🚚 Move Constructor**         | Efficiently "steals" resources from temporary objects |
| **5.  🚛 Move Assignment Operator** | Transfers ownership during assignment                 |

This avoids unnecessary deep copies and allows transfer of ownership.

---

## 💡 Example: Managing Dynamic Memory

```cpp
class MyClass {
private:
    int* data;

public:
    // 1. Destructor
    ~MyClass() {
        delete[] data;
    }

    // 2. Copy constructor
    MyClass(const MyClass& other) {
        data = new int[*other.size];
        // copy content from other.data
    }

    // 3. Copy assignment
    MyClass& operator=(const MyClass& other) {
        if (this == &other) return *this; // self-assignment check
        delete[] data;
        data = new int[*other.size];
        // copy content from other.data
        return *this;
    }

    // 4. Move constructor
    MyClass(MyClass&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }

    // 5. Move assignment
    MyClass& operator=(MyClass&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        other.data = nullptr;
        return *this;
    }
};

```

### 🧠 Quick heuristic

| If your class uses                 | You probably need                                     |
| ---------------------------------- | ----------------------------------------------------- |
| Raw pointers                       | Rule of 5                                             |
| `std::string`, `std::vector`, etc. | Rule of 0 (compiler does it well)                     |
| Smart pointers                     | Rule of 5 (but use `std::unique_ptr`, then move-only) |

---
# 1. Copy Constructor (Rule of 5)

## 🧠 Why It's Needed

When you create a **new object** as a **copy of an existing one**, the copy constructor defines how the copy is performed.

The default copy constructor does a **shallow copy**, which is dangerous if your class manages resources on the heap. You need a **deep copy** to ensure safety and correctness.

## ✳️ Syntax

```cpp
class Person {
    char* name;

public:
    // Custom Copy Constructor
    Person(const Person& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
};
```

## 💡 What It Does

* Allocates **new memory** for the copied object's resource
* Copies values instead of just copying the pointer address

## 🧪 Example

```cpp
Person p1("Alice");
Person p2 = p1; // Copy constructor is called

p1.display();  // Alice
p2.display();  // Alice

p1.setName("Zoe");

p1.display();  // Zoe
p2.display();  // Alice ✅ (No corruption)
```

## ⚠️ Without It?

* Both objects may point to the **same memory** (shallow copy)
* Modifying one will affect the other
* Destructor will be called **twice** on the same memory (💥 crash)

## ✅ When to Use It

* Your class has raw pointers or resources that need their own copy

## 🚨 Best Practices

* Always define a copy constructor if your class uses dynamic memory
* Pair with a proper destructor and copy assignment operator

---
# 2. Destructor (Rule of 5)

## 🧠 Why It's Needed

Any time your class allocates resources (like memory on the heap), you **must** release them when the object is destroyed. The **destructor** ensures proper cleanup and prevents **memory leaks**.

Without a destructor, your program may leave allocated memory or open handles hanging, causing poor performance or even crashes.

## ✳️ Syntax

```cpp
class Person {
    char* name;

public:
    // Destructor
    ~Person() {
        delete[] name;
    }
};
```

## 💡 What It Does

* Gets automatically called when an object goes **out of scope** or is **deleted**
* Cleans up dynamic resources (e.g., `delete[]`, `close()`, `fclose()`)

## 🧪 Example

```cpp
void createPerson() {
    Person p("Alice");
    // Destructor automatically called when p goes out of scope
}
```

## ⚠️ Without It?

* You may get **memory leaks**
* Heap memory won't be released properly
* Other resources like file handles or sockets may remain open

## ✅ When to Use It

* Your class uses `new`, `new[]`, or handles any system resource (like file descriptors, sockets, etc.)

## 🚨 Best Practices

* Always define a destructor if your class manages **raw resources**
* Use `delete[]` if you used `new[]`, and `delete` if you used `new`
* If your class uses **smart pointers**, you may not need a custom destructor

--- 
# 3. Copy Assignment Operator (Rule of 5)

## 🧠 Why it's Needed

When an object holds **resources on the heap**, and you assign one object to another (after both are already constructed), C++ calls the **copy assignment operator**.

If you don’t define your own, the compiler does a **shallow copy** — which copies the pointer value, not the memory it points to. This causes two objects to share the same resource and can lead to crashes (double deletion) or corruption.

## ✳️ Syntax

```cpp
class Person {
    char* name;

public:
    // Copy Assignment Operator
    Person& operator=(const Person& other) {
        if (this == &other) return *this; // Handle self-assignment

        delete[] name; // Clean up existing resource
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name); // Deep copy

        return *this;
    }
};
```

## 💡 What it Does

* Checks for self-assignment
* Frees the current object’s memory (`delete[] name`)
* Allocates new memory and copies data
* Returns a reference to `*this` so it can chain: `a = b = c;`

## 🧪 Example of the Danger Without It

```cpp
Person p1("Alice");
Person p2("Bob");

p2 = p1;  // compiler-provided shallow copy

p1.display(); // Alice
p2.display(); // Alice (so far, seems fine)

p1 = "Zoe"; // ⚠️ Direct assignment like this isn’t safe and will crash if not overloaded

p1.display(); // Undefined
p2.display(); // Could also be corrupted
```

Without a proper copy assignment operator:

* `p2 = p1` copies the pointer, not the contents
* Both `p1` and `p2` point to the same memory
* Modifying or deleting one affects the other

## ⚠️ Don't Forget

If your class allocates resources:

* Always write a custom copy assignment operator
* Combine it with a destructor, copy constructor, move constructor, and move assignment operator — **Rule of 5**

| Problem              | What Copy Assignment Solves                 |
| -------------------- | ------------------------------------------- |
| Shallow copy         | Prevents shared pointers and double-deletes |
| Memory leaks         | Ensures memory is cleaned properly          |
| Correct object state | Guarantees true deep copies                 |

---

# 4. Move Constructor (Rule of 5)

## 🧠 Why it's needed

When an object owns **heap resources**, a **copy constructor** duplicates them (deep copy). But sometimes, we don't need to copy — we just want to **transfer** ownership of those resources to a new object. That’s where the **move constructor** comes in: it's faster and avoids unnecessary allocations.

## ✳️ Syntax

```cpp
class Person {
    char* name;

public:
    // Move Constructor
    Person(Person&& other) noexcept {
        name = other.name;      // transfer ownership
        other.name = nullptr;   // null out the source
    }
};
```

`Person&&` means an **rvalue reference** — a temporary object you can "steal" from.

## 💡 What it Does

Instead of copying `other.name`, it **steals** the pointer:

* `this->name = other.name`
* Then: `other.name = nullptr` so that `other` doesn't delete it later (avoids double free)

## 🧪 Example

```cpp
Person p1("Alice");
Person p2 = std::move(p1); // move constructor called

p2.display();  // Alice
p1.display();  // null or garbage — ownership is gone
```

## 🧱 Without Move Constructor

If you don’t define a move constructor and use `std::move`, the compiler falls back to the copy constructor — defeating the point of move semantics. Worse, it may still shallow copy unless your copy is deep.

## ⚠️ Don't Forget

If you implement a move constructor:

* You should **nullify** the source's pointer (`other.name = nullptr`)
* Mark it `noexcept` when possible for performance (important for STL containers like `std::vector`)

--- 
# 5 Move Assignment Operator (Rule of 5)

## 🧠 Why It's Needed

When working with **heap-allocated resources**, simply moving ownership from one object to another is often more efficient than copying. The **move assignment operator** allows this by transferring ownership instead of duplicating resources.

Without a move assignment operator, moving objects may fall back to the copy assignment operator — which can be expensive.

## ✳️ Syntax

```cpp
class Person {
    char* name;

public:
    // Move Assignment Operator
    Person& operator=(Person&& other) noexcept {
        if (this == &other) return *this; // Handle self-assignment

        delete[] name; // Clean up existing resource

        name = other.name;     // Steal the pointer
        other.name = nullptr;  // Leave source in a safe state

        return *this;
    }
};
```

## 💡 What It Does

* Checks for self-assignment
* Destroys current owned memory
* Transfers the pointer (not the content)
* Nullifies the source to prevent double-free
* Returns `*this` for chaining

## 🧪 Example

```cpp
Person p1("Alice");
Person p2("Bob");

p2 = std::move(p1); // Move assignment

p2.display(); // Alice
p1.display(); // Empty or safe default (nullptr)
```

## ⚠️ Without It?

If you don’t define a move assignment operator:

* The compiler may use the **copy assignment** (costly for large resources)
* You may get unintended sharing or leaks if manually handling pointers

## ✅ When to Use It

* Your class manages **raw pointers** or **unique resources** (e.g., file handles, memory buffers)
* You want to avoid deep copying in performance-critical paths

## 🚨 Don’t Forget:

* Always combine this with:

    * Destructor
    * Copy constructor
    * Copy assignment operator
    * Move constructor

---
## 📌 Summary

| Function                 | When It’s Called                         |
| ------------------------ | ---------------------------------------- |
| Destructor               | When object is destroyed                 |
| Copy Constructor         | When object is initialized from another  |
| Copy Assignment Operator | When object is assigned from another     |
| Move Constructor         | When initialized with temporary (rvalue) |
| Move Assignment Operator | When assigned from temporary (rvalue)    |

Following the Rule of Three or Five ensures correct memory and resource management, preventing issues like memory leaks, double deletion, or shallow copies.
