#include <iostream>

// int charAsInt(char c)
// {
// 	return c;
// }

// int getInt(int c)
// {
// 	return c;
// }

int main()
{
    std::cout << "Enter a single character: ";
    int8_t character {};
    // char character {};
    std::cin >> character;

    std::cout << "You Entered '" << character << "', which has ASCII code " << static_cast<int>(character) << ".\n"; // Explicit conversion
    std::cout << "You Entered '" << character << "', which has ASCII code " << int {character} << ".\n"; // implicit conversion
    // std::cout << "You entered '" << c << "', which has ASCII code " << charAsInt(c) << ".\n";
    // std::cout << "You entered '" << c << "', which has ASCII code " << getInt(c) << ".\n";
    return 0;
}
