#ifndef FOOD_H
#define FOOD_H
#include "includes.h"
#include <string>

class Food{
public:
	Food(long code,std :: string name,FoodType type,int cost);
	FoodType getType(){return type;};
	long getCode(){return code;};
	int getCost(){return cost;};
	string getName(){return name;};
private:
	long code;
	string name;
	FoodType type;
	int cost;
};

#endif
