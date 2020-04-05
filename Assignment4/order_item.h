#ifndef ORDERITEM_H
#define ORDERITEM_H
#include "includes.h"
class OrderItem{
public:
	OrderItem(int restaurantIndex,int foodIndex,int amount,string description)
	:amount(amount),description(description),restaurantIndex(restaurantIndex),foodIndex(foodIndex){};
	int getRestaurantIndex(){return restaurantIndex;};
	int getFoodIndex(){return foodIndex;};
	int getAmount(){return amount;};
	string getDescription(){return description;};
private:
	int restaurantIndex;
	int foodIndex;
	int amount;
	string description;
};
#endif