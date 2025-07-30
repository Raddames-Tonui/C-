#include <iostream>
#include <memory> // For smart pointers

using namespace std;

/*
 * ------   CLASSES ----------
 */
class Vehicle {
private:
    string name;
    int size;             //  Data Member
    static int count;     // Static member variable: shared across all objects

public:
    // ----- Constructors----
    //  Default
    Vehicle()  {
        name = "Unknown";
        size = 0;
        count++; // increment when vehicle is created
    }

    // Parameterized
    Vehicle(string n, int s) {
        name = n;
        size = s;
        count++;
    }

    //------- Destructor ------
    ~Vehicle() {
        cout << "Destructor called for vehicle: " << name << endl;
        count--;
    }
    // -------Getters and Setters --------
    string getName() const {
        return name;
    }

    int getSize() const {
        return size;
    }

    void setName(string name) {
        this->name = name;
    }

    void setSize(int size) {
        this->size = size;
    }

    // Regular Member Function
    void showDetails() {
        cout << "Vehicle name: " << name << ", Size: "<< size <<" tonnes"<< endl;
    }

    // Static function: Can access only static members
    static void totalVehicles() {
        cout << "\nTotal number of vehicles: " << count << endl;
    };
};

// Static member definition (must be done outside the class)
int Vehicle::count = 0;


void basicClassFunction() {
    Vehicle v1("Truck", 15);
    Vehicle v2("Car", 3);
    Vehicle v3;
    Vehicle v4;

    v3.setName("Motorbike");
    v3.setSize(1);

    v1.showDetails();
    v2.showDetails();
    v3.showDetails();

    // Call static function with clas Name
    Vehicle::totalVehicles();
}

// ------- DANGLING POINTER --------
// after destruction
void danglingPointerExample() {
    Vehicle* vptr = new Vehicle("Semi", 10); // Dynamically allocated space
    vptr-> showDetails();
    delete vptr;            // Freed Memory, but pointer points to freed memory

    vptr -> showDetails();  // Undefined Behavior — accessing deleted memory!
    vptr = nullptr;         // Pointer nullified

    /*
     * Result: Segmentation fault (crash)
     * 0xC0000005 — Access Violation (Segmentation Fault)
     */
    vptr -> showDetails();
}
/*
 *  --- VOID POINTERS -------
 *  A void* is a generic pointer that can hold the address of any data type.
 *  Used when the type is unknown or varies
 *  You cannot dereference or perform arithmetic on a void* directly.
 *  It must be cast back to a specific type before usage.
 */
void voidPointerExample(void* data, const string& type) {
/**
 *  Casting a void* to an int*
 *  (int*)data  => This tells the compiler: "Trust me, data points to an int."
 *  *((int*)data) => Dereferencing the resulting int*
 *  The outer * retrieves the actual value at that memory location.
 */
    if (type == "int")
        cout << *((int*)data) << endl;
    else if (type == "float")
        cout << *((float*)data) << endl;
    else if (type == "string")
        cout << *((string*)data) << endl;
    else if (type == "char")
        cout << *((char*)data) << endl;
    else
        cout << "Unknown type!" << endl;
}

// Void pointer to an array
void voidPointerArrayExample(void* data, const string& type, int length) {
    if (type == "int") {
        int* arr = (int*)data;
        for (int i = 0; i < length; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }
    else if (type == "float") {
        float* arr = (float*)data;
        for (int i = 0; i < length; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }
    else if (type == "string") {
        string* arr = (string*)data;
        for (int i = 0; i < length; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }
    else if (type == "char") {
        char* arr = (char*)data;
        for (int i = 0; i < length; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }
    else
        cout << "Unknown type!" << endl;
}


void testVoidPointerExample() {
    int age = 10;
    float height = 5.67f;
    string name = "Raddames";
    char bloodtype = 'O';
    char grade = 'A';

    voidPointerExample(&age, "int");
    voidPointerExample(&height, "float");
    voidPointerExample(&name, "string");
    voidPointerExample(&bloodtype, "char");
    voidPointerExample(&grade, "char");

    // Using arrays
    int nums[] = {1, 2, 3, 4, 5};
    float fnums[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    char chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    string names[] = {"james", "hellen", "beatrice"};

    voidPointerArrayExample(nums, "int", 5);
    voidPointerArrayExample(fnums, "float", 5);
    voidPointerArrayExample(chars, "char", 8);
    voidPointerArrayExample(names, "string", 3);

}



/*
 *  --- UNIQUE SMART POINTERS ---
 *  Exclusive ownership — only one unique_ptr can own the object at a time.
 */
void usingUniqueSmartPointers() {
    unique_ptr<Vehicle> v6 = make_unique<Vehicle>("Bus", 16);
    unique_ptr<Vehicle> v7 = make_unique<Vehicle>("Car", 3);

    v6->showDetails();
    v7->showDetails();

    Vehicle::totalVehicles();

    unique_ptr<Vehicle> v8 = move(v6);
    // v6->showDetails();  // Causes Segmentation fault (crash)
    // v8 -> showDetails();
}// v6 and v7 go out of scope here, memory is released automatically

/*
 *  --- SHARED SMART POINTERS ---
 *  Object is deleted only when the last shared_ptr is destroyed.
 *  use_count() tells you how many shared_ptr instances share ownership.
 */
void usingSharedSmartPointers() {
    shared_ptr<Vehicle> v1 = make_shared<Vehicle>("Saloon", 3);
    shared_ptr<Vehicle> v2 = make_shared<Vehicle>();

    v1->showDetails();
    v2->showDetails();
    Vehicle::totalVehicles();
    {
        // Another shared_ptr pointing to the same Vehicle
        shared_ptr<Vehicle> v3 = v1;  // v3 now shares ownership of the same vehicle as v1 ("Saloon")
        v3->showDetails();
        cout << "V1 Use count: " << v1.use_count() << endl; // Ref count for "Saloon" =  2
        Vehicle::totalVehicles();
    }
    Vehicle::totalVehicles();
}

/*
*  --- WEAK SMART POINTERS ---
*  non-owning reference to an object managed by a shared_ptr
*   must call .lock() to access the object as a temporary shared_ptr
*  If the object has already been deleted, .lock() returns nullptr
*  Helps prevent cyclic references, which cause memory leaks.
*  // A -> B -> A (cycle), both are shared_ptrs => memory leak!
*  Cleaner code via RAII (Resource Acquisition Is Initialization).
*/


int main() {
    testVoidPointerExample();
   // basicClassFunction();
    // danglingPointerExample();
    // usingUniqueSmartPointers();
    // usingSharedSmartPointers();


    // Vehicle::totalVehicles();

    return 0;
}