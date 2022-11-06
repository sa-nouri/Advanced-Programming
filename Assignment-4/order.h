#ifndef ORDER_H
#define ORDER_H
#include "order_item.h"
#include "includes.h"
#include "restaurant.h"
#include "food.h"
struct costStatus{
	bool ignoreDelivery;
	int totalPrice;
	costStatus(bool ignoreDelivery,int totalPrice):ignoreDelivery(ignoreDelivery),totalPrice(totalPrice){};
};
class Order{
public:
	costStatus calculateTotalCost(string customerRegion,vector<Restaurant>& restaurants);
	void addItem(int restaurantIndex,int foodIndex,int amount,string description){
		orderItems.push_back(OrderItem(restaurantIndex,foodIndex,amount,description));};
	vector<OrderItem> getOrderItems(){return orderItems;}; 

private:
	vector<OrderItem> orderItems;
};
#endif