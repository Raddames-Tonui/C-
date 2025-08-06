#include <iostream>
#include <string>
using namespace std;

/**
 * Base class Animal, virtually inherited to allow diamond inheritance.
 * Contains a raw pointer member `name` to demonstrate manual memory management.
 */
class Animal {
protected:
    string* name; // raw pointer to dynamically allocated string

public:
    // Explicit constructor to avoid accidental implicit conversions
    explicit Animal(const string& name) {
        this->name = new string(name); // allocate string on heap
        cout << "Animal constructor for: " << *this->name << endl;
    }

    // Copy constructor (deep copy)
    Animal(const Animal& other) {
        name = new string(*other.name); // deep copy
        cout << "Animal copy constructor for: " << *name << endl;
    }

    // Copy assignment operator (deep copy)
    Animal& operator=(const Animal& other) {
        if (this != &other) {
            delete name; // delete current
            name = new string(*other.name); // deep copy
        }
        cout << "Animal assignment for: " << *name << endl;
        return *this;
    }

    // Virtual function to be overridden by derived classes
    virtual void speak() const {
        cout << *name << " makes a sound (from Animal)." << endl;
    }

    // Getter to safely access name
    /**
     *
     * @return If someone calls getName() and ignores the returned value,
     * the compiler may issue a warning.
     */
    [[nodiscard]] string getName() const {
        return *name;
    }

    // Virtual destructor to ensure derived destructors are called
    virtual ~Animal() {
        cout << "Animal destructor for: " << *name << endl;
        delete name; // free allocated memory
    }

    void showAbilities();
};

/**
 * Flyer class inherits virtually from Animal to support diamond inheritance.
 * Adds a raw pointer member `wingType`.
 */
class Flyer : virtual public Animal {
protected:
    string* wingType;

public:
    Flyer(const string& name, const string& wing)
        : Animal(name) {
        wingType = new string(wing);
        cout << "Flyer constructor for: " << getName() << ", Wings: " << *wingType << endl;
    }

    // Copy constructor (deep copy of wingType)
    Flyer(const Flyer& other) : Animal(other) {
        wingType = new string(*other.wingType);
        cout << "Flyer copy constructor for: " << getName() << endl;
    }

    // Copy assignment operator
    Flyer& operator=(const Flyer& other) {
        if (this != &other) {
            Animal::operator=(other); // base copy
            delete wingType;
            wingType = new string(*other.wingType);
        }
        cout << "Flyer assignment for: " << getName() << endl;
        return *this;   // Returns a reference to the current object (not a pointer, and not a copy)
    }

    // Additional behavior
    virtual void fly() const {
        cout << getName() << " is flying with " << *wingType << " wings." << endl;
    }

    // Override speak
    void speak() const override {
        cout << getName() << " says: I can fly!" << endl;
    }

    // Destructor to free wingType
    ~Flyer() override {
        cout << "Flyer destructor for: " << getName() << endl;
        delete wingType;
    }

    void speaks();
};

/**
 * Swimmer class inherits virtually from Animal.
 * Adds a raw pointer member `fins` (integer).
 */
class Swimmer : virtual public Animal {
protected:
    int* fins; // pointer to int for fin count

public:
    Swimmer(const string& name, int finsCount)
        : Animal(name) {
        fins = new int(finsCount); // allocate on heap
        cout << "Swimmer constructor for: " << getName() << ", Fins: " << *fins << endl;
    }

    // Copy constructor
    Swimmer(const Swimmer& other) : Animal(other) {
        fins = new int(*other.fins); // deep copy
        cout << "Swimmer copy constructor for: " << getName() << endl;
    }

    // Assignment operator
    Swimmer& operator=(const Swimmer& other) {
        if (this != &other) {
            Animal::operator=(other);
            delete fins;
            fins = new int(*other.fins);
        }
        cout << "Swimmer assignment for: " << getName() << endl;
        return *this;
    }

    // Additional behavior
    virtual void swim() const {
        cout << getName() << " is swimming with " << *fins << " fins." << endl;
    }

    // Override speak
    void speak() const override {
        cout << getName() << " says: I can swim!" << endl;
    }

    // Destructor to free fins
    ~Swimmer() override {
        cout << "Swimmer destructor for: " << getName() << endl;
        delete fins;
    }
};

/**
 * Duck inherits from both Flyer and Swimmer — demonstrating diamond inheritance.
 * Adds an extra pointer member `weight`.
 */
class Duck : public Flyer, public Swimmer {
private:
    double* weight; // pointer to duck's weight

public:
    // Constructor initializes all base and own members
    Duck(const string& name, const string& wing, int finsCount, double wt)
        : Animal(name), Flyer(name, wing), Swimmer(name, finsCount) {
        weight = new double(wt); // dynamically allocate weight
        cout << "Duck constructor for: " << getName() << ", Weight: " << *weight << " kg\n";
    }

    // Copy constructor
    Duck(const Duck& other)
        : Animal(other), Flyer(other), Swimmer(other) {
        weight = new double(*other.weight);
        cout << "Duck copy constructor for: " << getName() << endl;
    }

    // Assignment operator
    Duck& operator=(const Duck& other) {
        if (this != &other) {
            Flyer::operator=(other);
            Swimmer::operator=(other);
            delete weight;
            weight = new double(*other.weight);
        }
        cout << "Duck assignment for: " << getName() << endl;
        return *this;
    }

    // Override speak to include weight
    void speak() const override {
        cout << getName() << " says: Quack! I'm a duck! I weigh " << *weight << " kg.\n";
    }

    // Demonstrate abilities from both parents
    void showAbilities() const {
        fly();
        swim();
    }


    void showDetails() const {
        cout << "-------------DETAILS-------------" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Wing Type: "<< *wingType << endl;
        cout << "Fins: " << *fins << endl;
        cout << "Weight: " << *weight << endl;
    }

    // Destructor to clean up weight
    ~Duck() override {
        cout << "Duck destructor for: " << getName() << endl;
        delete weight;
    }
};

/**
 * Demonstrates raw pointer parameter — used polymorphically
 */
void inspect(Animal* a) {
    cout << "[Raw Pointer Inspect] ";
    a->speak(); // virtual function call
}

int main() {
    cout << "\n=== 1. Stack Object Creation ===" << endl;
    Duck d1("Daffy", "Feathery", 2, 4.5); // stack allocation

    cout << "\n=== 2. Heap Object Creation (Raw Pointer) ===" << endl;
    Duck* d2 = new Duck("Donald", "Short", 5, 3.9); // heap allocation

    cout << "\n=== 3. Accessing Member Functions ===" << endl;
    cout << "-> d1 speaks: ";
    d1.speak(); // via object

    cout << "-> d2 speaks: ";
    d2->speak(); // via pointer

    cout << "\n=== 4. Calling Custom Behaviors ===" << endl;
    d1.showAbilities(); // swim + fly
    d2->showAbilities();

    cout << "\n=== 5. Copy Constructor ===" << endl;
    Duck d3 = d1; // invokes copy constructor
    d1.showDetails();
    d3.showDetails();
    d3.Swimmer::swim();

    cout << "\n=== 6. Assignment Operator ===" << endl;
    d3 = *d2; // invokes copy assignment
    d2->showDetails();
    d3.showDetails();
    d3.Swimmer::swim();

    cout << "\n=== 7. Accessing Raw Pointer Members (indirectly) ===" << endl;
    cout << "Name via d1: " << d1.getName() << endl;
    cout << "Name via d2: " << d2->getName() << endl;

    cout << "\n=== 8. Reference Usage ===" << endl;
    Duck& ref = d1;
    ref.speak(); // same as d1
    Duck& ref2 = *d2;
    ref2.speak();

    cout << "\n=== 9. Polymorphism with Raw Pointer ===" << endl;
    Animal* a = d2; // base class pointer to derived object
    a->speak(); // dynamic binding — Duck::speak()

    cout << "\n=== 10. Function Chaining ===" << endl;
    // Not meaningful here, but we’ll simulate assignment chaining
    Duck d4("Temp", "Stub", 0, 1.0);
    (d4 = d1) = d3;
    d4.speak(); // should now match d3

    cout << "\n=== 11. Clean up heap object ===" << endl;
    delete d2;

    cout << "\n=== END ===" << endl;

    int ex = 'b';
    cout << ex << endl;
    return 0;
}



// int main() {
//     // cout << "=== Creating Duck ===\n";
//     // Animal* daffy = new Duck("Daffy", "Feathery", 2, 4.5);
//     //
//     //
//     // cout << "\n=== Demonstrate Abilities ===\n";
//     // daffy->speak();
//     // daffy->showAbilities();
//     //
//     // cout << "\n=== Passing to Raw Pointer Function ===\n";
//     // inspect(daffy);
//     //
//     // cout << "\n=== Deleting Duck ===\n";
//     // delete daffy; // calls destructors from Duck → Swimmer → Flyer → Animal
//
//     Duck d1("Daffy", "Feathery", 2, 4.5); // stack
//     Duck* d2 = new Duck("Donald", "short", 7, 23); // Heap
//     d1.showDetails();
//     d2->showDetails();
//     d1.Swimmer::swim();
//     d2->Swimmer::swim();
//     d2 -> speak();
//
//     delete d2;
//
//     return 0;
// }


































/**
* | Concept                      | Where It's Shown                                                  |
| ---------------------------- | ----------------------------------------------------------------- |
| Diamond inheritance          | `Duck` ← `Flyer`, `Swimmer` ← `Animal`                            |
| Virtual inheritance          | `Flyer`, `Swimmer` use `virtual public Animal`                    |
| Raw pointer members          | `string* name`, `string* wingType`, `int* fins`, `double* weight` |
| Manual memory management     | All constructors, destructors, copy/assignment                    |
| Polymorphism via raw pointer | `inspect(Animal*)`                                                |
| `explicit` constructor       | Prevents implicit `Animal a = "Duck"` mistakes                    |

 */