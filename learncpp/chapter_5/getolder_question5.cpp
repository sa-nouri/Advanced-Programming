#include <iostream>
#include <string>

std::string getName(int numName){
    std::cout << "Enter the name of person #" << std::to_string(numName) << ":\n";
    
    std::string name;
    // std::cin >> name; # problem with spaces
    std::getline(std::cin >> std::ws, name);
    return name;
}

// int getAge(std::string_view name)
int getAge(std::string name){

    std::cout << "Enter the age of " << name << ":\n";

    int  age;
    std::cin >> age;
    return age;
}

void compareAges(){
    const std::string  first_name { getName(1) };
    const int first_age { getAge(first_name) };

    const std::string  second_name { getName(2) };
    const int second_age { getAge(second_name)};

    // // David Jenkins (age 44) is older than John Bacon (age 37).
    if(first_age > second_age)
        std::cout << first_name << " (age " << std::to_string(first_age) << ") is older than " << second_name << " (age " << std::to_string(second_age) << ").\n";
    else if (second_age > first_age)
        std::cout << second_name << " (age " << std::to_string(second_age) << ") is older than " << first_name << " (age " << std::to_string(first_age) << ").\n";
}

// void printOlder(std::string_view name1, int age1, std::string_view name2, int age2)
// {
//     if (age1 > age2)
//         std::cout << name1 << " (age " << age1 <<") is older than " << name2 << " (age " << age2 <<").\n";
//     else
//         std::cout << name2 << " (age " << age2 <<") is older than " << name1 << " (age " << age1 <<").\n";
// }

int main(){
    compareAges();

    return 0;
}
