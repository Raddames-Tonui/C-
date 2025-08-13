#include "Pupil.h"

// Constructor implementation
Pupil::Pupil(const std::string& firstName, const std::string& lastName)
    : firstName_(firstName), lastName_(lastName) {}

// Method implementation
std::string Pupil::getFullName() const {
    return firstName_ + " " + lastName_;
}
