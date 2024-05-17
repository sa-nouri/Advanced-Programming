#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t option_viewed{ 0x01 };
    [[maybe_unused]] constexpr std::uint8_t option_edited{ 0x02 };
    [[maybe_unused]] constexpr std::uint8_t option_favorited{ 0x04 };
    [[maybe_unused]] constexpr std::uint8_t option_shared{ 0x08 };
    [[maybe_unused]] constexpr std::uint8_t option_deleted{ 0x10 };

    std::uint8_t myArticleFlags{ option_favorited };

    // Place all lines of code for the following quiz here

    // Add a line of code to set the article as viewed.
    myArticleFlags |= option_viewed;

    // Add a line of code to check if the article was deleted.
    if (myArticleFlags & option_deleted)
        std::cout << "Article Was Deleted!";
    
    // Add a line of code to clear the article as a favorite.
    myArticleFlags &= static_cast<std::uint8_t>(~option_favorited);

    // Extra credit: why are the following two lines identical?
    // myflags &= ~(option4 | option5); // turn options 4 and 5 off
    // myflags &= ~option4 & ~option5; // turn options 4 and 5 off

    std::cout << std::bitset<8>{ myArticleFlags } << '\n';

    return 0;
}
