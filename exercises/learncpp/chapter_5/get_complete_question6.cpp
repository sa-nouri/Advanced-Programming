#include <iostream>
#include <string>

// Write the function getQuantityPhrase() here
constexpr std::string_view getQuantityPhrase(int quantity){

    if (quantity == 0)
        return "no";
    else if (quantity == 1)
        return "a single";
    else if (quantity == 2)
        return "a couple of";
    else if (quantity == 3)
        return "a few of";
    else if (quantity > 3)
        return "many";
    return "negative"; 
}
// Write the function getApplesPluralized() here
constexpr std::string_view getApplesPluralized(int quantity){
    // return (num == 1) ? "apple" : "apples";
    if (quantity == 1)
        return "apple";
    return "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}
