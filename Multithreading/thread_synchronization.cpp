#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std;

// ---------------- Shared resource WITHOUT mutex ----------------
double val1 = 0;
int cnt1 = 0;

void addUnsnc (double num) {
    double tempVal = val1;
    int tempCnt = cnt1;
    this_thread::sleep_for(1ms);     // Pauses the execution of the current thread for a specified duration.
    tempVal += num;
    tempCnt += 1;
    val1 = tempVal;
    cnt1 = tempCnt;
    cout << "[Unsync] Thread " << cnt1 << " -> val = " << val1 << endl;
}

// ---------------- Shared resource WITH mutex ----------------
// A mutex is used to protect shared data between threads to prevent data races and ensure synchronization.
double val2 = 0;
int cnt2 = 0;
mutex mtx;

void addSync (double num) {
    lock_guard<mutex> lock(mtx); // automatically locks/ unlocks
    val2 += num;
    cnt2 ++;
    cout << "[Sync] Thread " << cnt2 << " -> val = " << val2 << endl;
}

// ---------------- Shared resource WITH condition_variable ----------------
double val3 = 0;
int cnt3 = 0;
mutex mtx3;
condition_variable cv;   // Used to synchronize threads, allowing one thread to wait for a condition before proceeding.
bool ready = false;

void addCondition(double num) {
    unique_lock<mutex> lock(mtx3);
    cv.wait(lock, []{return ready;}); // wait until main signals ready
    val3 += num;
    cnt3++;
    cout << "[CondVar] Thread " << cnt3 << " -> val = " << val3 << endl;
}



int main () {

    cout << "-------Unsynchronized thread-------" << endl;
    thread ut1(addUnsnc, 4);
    thread ut2(addUnsnc, 6);
    ut1.join();
    ut2.join();
    cout << "[Unsync] Final val = " << val1 << ", cnt = " << cnt1 << endl << endl;

    cout << "-------Synchronized threads (mutex)--------" << endl;
    thread st1(addSync, 4);
    thread st2(addSync, 6);
    st1.join();
    st2.join();
    cout << "[Sync]   Final val = " << val2 << ", cnt = " << cnt2 <<"\n"<< endl;

    cout << "------- Threads waiting on Condition_variable-------" << endl;
    thread cv1(addCondition, 4);
    thread cv2(addCondition, 6);

    cout << "Thread ID (Get_id): " << cv2.get_id() << endl;   // Retrieves the unique ID of the current thread

    this_thread::sleep_for(10ms);
    {
        lock_guard<mutex> lock(mtx3);  // A wrapper for mutexes that automatically locks and unlocks the mutex in a scoped block.
        ready = true;
    }
    cv.notify_all(); // wake all waiting threads

    cv1.join();
    cv2.join();
    cout << "[CondVar] Final val = " << val3 << ", cnt = " << cnt3 << endl;
    return 0;
}