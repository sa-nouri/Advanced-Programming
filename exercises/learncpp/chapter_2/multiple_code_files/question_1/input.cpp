#include <iostream>

int getInteger()
{
    std::cout << "Enter an Integer: ";
    int x{};
    std::cin >> x;
    return x;
}
