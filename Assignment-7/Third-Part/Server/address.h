#ifndef ADDRESS_H
#define ADDRESS_H
#include "bad_address.h"
#include "universe.h"

class Address{
public:
	Address(std::string);
	int distanceWith(const Address&)const;
	 std::string toStr();
private:
	Planet* planet;
	Galaxy* galaxy;
	static Universe universe;
	
};
#endif