#include <iostream>

int readNumber()
{
    std::cout << "Enter an Integer: ";
    int num{};
    std::cin >> num;
    return num;
}

void writeAnswer(int num)
{
    std::cout << "The output answer is: " << num << ".\n";
}
