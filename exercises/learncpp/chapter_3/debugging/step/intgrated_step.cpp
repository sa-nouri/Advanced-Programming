#include <iostream>

void printValue(int value)
{
    std::cout << value << '\n';
}

int main()
{
    std::cout << std::unitbuf; // enable automatic flushing for std::cout (for debugging)
    printValue(5);

    return 0;
}
