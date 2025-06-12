#include <iostream>

int main()
{
    std::cout << "Enter an Integer: ";
    
    int num{};
    std::cin >> num;

    // int double_num{num * 2};
    // std::cout << "Double that number is:" << double_num << std::endl;

    // Another solution for the mentioned problem to reduce complexity
    // std::cout << "Double that number is: " << num * 2 << "\n";
    // std::cout << "Triple that number is: " << num * 3 << "\n";
    std::cout << "Double " << num << " is: " << num * 2 << "\n";
    std::cout << "Triple " << num << " is: " << num * 3 << "\n";
    return 0;
}
