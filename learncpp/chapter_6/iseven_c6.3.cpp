#include <iostream>

constexpr void isEven(int number)
{
    if (number % 2 == 0)
        std::cout << number << " is even.";
    else if (number  % 2 != 0)
        std::cout << number << " is odd.";
    
}

int main()
{
    std::cout <<  "Enter a number:";
    int number {};
    std::cin >> number;

    isEven(number);
    
    return 0;
}

// constexpr bool isEven(int x)
// {
//     // if x % 2 == 0, 2 divides evenly into our number, which means it must be an even number
//     return (x % 2) == 0;
// }

// # Rewrite with operator !
// bool isEven(int x)
// {
//     return !(x % 2);
// }

// int main()
// {
//     std::cout << "Enter an integer: ";
//     int x{};
//     std::cin >> x;

//     if (isEven(x))
//         std::cout << x << " is even\n";
//     else
//         std::cout << x << " is odd\n";

//     return 0;
// }
