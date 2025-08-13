#ifndef PUPIL_H
#define PUPIL_H

#include <string>

class Pupil {
public:
    Pupil(const std::string& firstName, const std::string& lastName);

    std::string getFullName() const;

private:
    std::string firstName_;
    std::string lastName_;
};

#endif // PUPIL_H
