//
// Created by Raddames on 29/07/2025.
//

#include "Dog.h"
#include <iostream>

Dog::Dog(const std::string& name, int age) : name(name), age(age) {}

std::string Dog::getName() const {
    return name;
}

int Dog::getAge() const {
    return age;
}

void Dog::setName(const std::string& name) {
    this->name = name;
}

void Dog::setAge(int age) {
    this->age = age;
}

void Dog::bark() const {
    std::cout << name << " says: Woof!" << std::endl;
}
