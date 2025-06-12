#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "order.h"
#include "includes.h"
#include "restaurant.h"
class Customer{
public:
	Customer(string _name,long _phone,string region);
	string getRegion(){return region;};
	long getPhone(){return phone;};
	string getName(){return name;};
	bool readOrder(vector<Restaurant>& restaurants);
	vector<Order> getOrders(){return orders;};
private:
	string name;
	long phone;
	string region;
	vector<Order> orders;
};
#endif
