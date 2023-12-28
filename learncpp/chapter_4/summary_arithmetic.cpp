#include <iostream>

double getValue()
{
    std::cout << "Enter a double value: ";
    double input{};
    std::cin >> input;
    
    return input;
}

char getOperator()
{
    std::cout << "Enter +, -, *, or /: ";
    char operator_{};
    std::cin >> operator_;

    return operator_;
}

double doOperand(double num_1, double num_2, char operator_)
{
    switch(operator_)
    {
        case '+':
            return num_1 + num_2;
        case '-':
            return num_1 - num_2;
        case '*':
            return num_1 * num_2;
        case '/':
            return num_1 / num_2;
        default:
            return 0;
    }
}

int main()
{
    double num_1{ getValue() };
    double num_2{ getValue() };

    char operator_{ getOperator() };
    // std::cout << "The number is: " << num_1 << ".\n";
    // std::cout << "The operator is: " << operator_ << ".\n";

    if(operator_ != '+' && operator_ != '-' && operator_ != '*' && operator_ != '/')
        return 0;

    double result {doOperand(num_1, num_2, operator_)};

    std::cout << num_1 << " " << operator_ << " " << num_2 << " is " << result << "\n";

    return 0;
}
