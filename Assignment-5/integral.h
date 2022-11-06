#ifndef INTEGRAL_H
#define INTEGRAL_H
#include "invalid_initial_value.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>
#include "invalid_digit_assignment.h"
class Integral {
	class proxy;
public:
	friend std::ostream& operator<<(std::ostream& out,const Integral& number);
	Integral();
	Integral(std::string str);
	Integral(int n);
	bool operator==(const Integral& number) const;
	bool operator<(const Integral& rightHand)const;
	Integral operator+(const Integral&)const;
	Integral diff(const Integral& arg) const;
	proxy operator[](int const idx);
	int operator[](int const idx)const;

private:
	void trim();
	std::vector<int> digits;

	class proxy{
        int value;
        std::vector<int>& subVector;
        int index;
    public:
        proxy(std::vector<int>& subVector,int value,int index) 
        : value(value) ,subVector(subVector),index(index){}

        proxy& operator=(int const& i);
        operator int();
    };
};
#endif