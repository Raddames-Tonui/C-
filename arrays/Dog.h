//
// Created by Raddames on 29/07/2025.
//

#ifndef DOG_H
#define DOG_H
#include <string>

class Dog {
private:
    std::string name;
    int age;

public:
    // Constructor
    Dog(const std::string& name, int age);

    // Getter methods
    std::string getName() const;
    int getAge() const;

    // Setter methods
    void setName(const std::string& name);
    void setAge(int age);

    // Behavior
    void bark() const;
};

#endif // DOG_H
