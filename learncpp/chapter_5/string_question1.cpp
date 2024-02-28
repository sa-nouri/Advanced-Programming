#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your age: ";
    int age{}; // age needs to be an integer, not a string, so we can do math with it
    std::cin >> age;

    // age is signed, and name.length() is unsigned -- we shouldn't mix these
    // We'll convert name.length() to a signed value
    int letters{ static_cast<int>(name.length()) }; // get number of letters in name (including spaces)
    std::cout << "Your age + length of name is: " << age + letters << '\n';

    return 0;
}
