#include <iostream>

int doubleNumber(int num)
{
    return num * 2;
}

int main()
{
    std::cout << "Enter an Integer: ";
    int num{};
    std::cin >> num;

    std::cout << "Double of " << num << " is " << doubleNumber(num) << "\n";

    return 0;
}
