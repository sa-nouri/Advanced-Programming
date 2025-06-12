// #include <cstdint> // for std::uint8_t # Should be removed!
#include <iostream>

int main()
{   
    std::cout << "How old are you?\n";

    // std::uint8_t age{}; # is not necessary
    int age{};
    std::cin >> age;

    std::cout << "Allowed to drive a car in Texas [";

    constexpr int license_age = 16;
    if (age >= license_age)
        // std::cout << "x"; # characters should be in single quotation
        std::cout << 'x';
    else
        std::cout << ' ';

    std::cout << "]\n";

    return 0;
}
