# C++ Concurrency Comprehensive Guide

## 1. Introduction

Concurrency in C++ allows multiple tasks to make progress independently. Unlike parallelism which requires multiple cores, concurrency focuses on **task management, scheduling, and safe coordination**.

## 2. Concurrency vs. Parallelism

* **Concurrency:** Multiple tasks can progress independently, possibly interleaving on a single core.
* **Parallelism:** Multiple tasks run simultaneously on multiple cores.

## 3. Challenges in Concurrency

* **Race conditions:** Shared data accessed by multiple threads.
* **Deadlocks:** Threads waiting on each other indefinitely.
* **Starvation:** Tasks never get CPU time.
* **Non-determinism:** Execution order is unpredictable.

## 4. C++ Tools for Concurrency

* **`std::thread`** → Basic thread creation.
* **`std::async` & `std::future`** → Run tasks asynchronously and retrieve results later.
* **`std::promise`** → Pass values between threads.
* **Thread pools** → Efficiently manage multiple tasks.
* **Synchronization primitives** (mutex, lock\_guard, condition\_variable) → Safe access to shared resources.
* **`std::atomic`** → Lock-free operations on shared data.

## 5. Example: `std::async`

```cpp
#include <future>
#include <iostream>

int compute(int x) { return x * x; }

int main() {
    std::future<int> result = std::async(std::launch::async, compute, 5);
    std::cout << "Doing other work...\n";
    int value = result.get();
    std::cout << "Result: " << value << std::endl;
}
```

* Tasks run concurrently.
* `std::async` manages threads internally.

## 6. Task-Based Concurrency

* Think in **tasks** rather than threads.
* Examples: processing transactions, generating reports, handling multiple network requests.
* Benefits: easier reasoning, better scalability, reduces manual thread management.

## 7. Best Practices

1. Minimize shared mutable state.
2. Prefer higher-level abstractions (`async`, `future`, thread pools).
3. Combine with mutexes and locks when necessary.
4. Test under load.

## 8. Visual Representation

![Concurrency Diagram](https://upload.wikimedia.org/wikipedia/commons/thumb/5/51/Concurrency_vs_parallelism.png/600px-Concurrency_vs_parallelism.png)
*Tasks interleaving and parallel execution visualization*

## 9. References

* [C++ Reference: `<thread>`](https://en.cppreference.com/w/cpp/thread)
* [C++ Reference: `<future>`](https://en.cppreference.com/w/cpp/thread/future)
* [C++ Concurrency Examples](https://www.geeksforgeeks.org/multithreading-in-cpp/)

---

This guide covers concurrency basics, challenges, tools, examples with async/future, task-based concurrency, and best practices.
