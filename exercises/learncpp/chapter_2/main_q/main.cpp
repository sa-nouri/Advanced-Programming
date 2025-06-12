#include "io.h"
#include <iostream>

int main()
{
    int first_num{ readNumber() };
    int second_num{ readNumber() };
    writeAnswer(first_num + second_num);
    return 0;
}
