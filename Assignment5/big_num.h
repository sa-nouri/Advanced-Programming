#ifndef BIG_NUM_H
#define BIG_NUM_H
#include <string>
#include <math.h>
#include <iostream>
#include "fractional.h"
#include "integral.h"
#include "invalid_initial_value.h"
class BigNum{
	class proxy;
	public:
		BigNum():negetive(false){};
		BigNum(std::string number);
		BigNum(double n);
		bool operator==(const BigNum& number) const;
		BigNum& operator=(BigNum other);
		BigNum operator-()const;
		bool operator<(const BigNum& rightHand)const;
		friend std::istream& operator>>(std::istream& in,BigNum& number);
		friend std::ostream& operator<<(std::ostream& out,const BigNum& number);
		BigNum operator+(const BigNum& arg)const;
		BigNum& operator+=(const BigNum& c);
		BigNum& operator++();
		BigNum operator++(int);
		proxy operator[](int const n);
    	int operator[](int const n)const;
	private:
		Integral integerPart;
		Fractional fractionalPart;
		bool negetive;


	class proxy{
        int value;
        void* subPart;
        int index;
    public:
        proxy(void* subPart,int value,int index) 
        : value(value) ,subPart(subPart),index(index){}

        proxy& operator=(int const& i);

        operator int();
    };
};
BigNum operator+(const double r, const BigNum& c);
#endif