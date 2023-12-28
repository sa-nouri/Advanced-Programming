#include <iostream>

int main()
{
    std::cout << "Enter a single character: ";
    int8_t character {};
    // char character {};
    std::cin >> character;

    std::cout << "You Entered '" << character << "', which has ASCII code " << static_cast<int>(character) << ".\n"; // Explicit conversion
    std::cout << "You Entered '" << character << "', which has ASCII code " << int {character} << ".\n"; // implicit conversion
    return 0;
}
