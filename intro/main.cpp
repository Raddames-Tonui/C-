#include <iostream>
#include <climits>    // For INT_MAX, INT_MIN, UINT32_MAX
#include <cstdint>    // For int32_t, uint32_t

// Signed Overflow (Undefined Behavior)
void testSignedOverflow() {
    std::cout << "--- Signed Overflow ---\n";

    int32_t signed_max = INT32_MAX;    // 2147483647
    int32_t signed_min = INT32_MIN;    // -2147483648

    std::cout << "Signed Max: " << signed_max << "\n";
    std::cout << "Signed Max + 1: " << (signed_max + 1) << "\n"; //  -2147483648 May wrap or cause undefined behavior

    std::cout << "Signed Min: " << signed_min << "\n";
    std::cout << "Signed Min - 1: " << (signed_min - 1) << "\n";  // wraps to 2147483647
}

// Unsigned Overflow (Defined Wrap-around)
void testUnsignedOverflow() {
    std::cout << "\n--- Unsigned Overflow ---\n";

    uint32_t unsigned_max = UINT32_MAX;  // 4294967295
    uint32_t unsigned_zero = 0;

    std::cout << "Unsigned Max: " << unsigned_max << "\n";
    std::cout << "Unsigned Max + 1: " << (unsigned_max + 1) << "\n"; // Wraps to 0

    std::cout << "Unsigned 0 - 1: " << (unsigned_zero - 1) << "\n"; // Wraps to 4294967295
}

// Check if types can hold negatives
void testNegativity() {
    std::cout << "\n--- Can Hold Negatives? ---\n";

    int32_t signed_val = -100;
    uint32_t unsigned_val = -100;

    std::cout << "Signed -100: " << signed_val << "\n";
    std::cout << "Unsigned -100: " << unsigned_val << "\n";   // wraps to 4294967196
}




int main() {
    testSignedOverflow();
    testUnsignedOverflow();
    testNegativity();

    return 0;
}
