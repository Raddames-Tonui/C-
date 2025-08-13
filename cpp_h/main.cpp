#include <iostream>
#include "Pupil.h"

int main() {
    Pupil p("Alice", "Mwangi");
    std::cout << p.getFullName() << std::endl;
    return 0;
}
