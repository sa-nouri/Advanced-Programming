#ifndef FRACT_H
#define FRACT_H
#include "invalid_initial_value.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>
#include "invalid_digit_assignment.h"
class Fractional {
	class proxy;
public:
	friend std::ostream& operator<<(std::ostream& out,const Fractional& number);
	Fractional();
	Fractional(std::string str);
	Fractional(int n);
	int getCarryOut();
	bool operator==(const Fractional& number) const;
	bool operator<(const Fractional& rightHand)const;
	Fractional operator+(const Fractional&)const;
	Fractional operator-(const Fractional&)const;
	proxy operator[](int const index);
    int operator[](int const index)const;
private:
	void trim();
	int carryOut;
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