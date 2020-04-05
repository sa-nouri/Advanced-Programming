#include "customer.h"
#include "restaurant.h"
Customer::Customer(string _name,long _phone,string _region){
	if(_name.size()==0||_phone>99999999999||_phone<10000000||_region.size()==0)
		abort();
	name=_name;
	phone=_phone;
	region=_region;
}
int findRestaurant(long phone,vector<Restaurant>&restaurants){
	for(int i=0;i<restaurants.size();i++)
		if(restaurants[i].getPhone()==phone)
			return i;
	return -1;
}
bool Customer::readOrder(vector<Restaurant>& restaurants){
	Order currentOrder;
	string line="";
	while(true){
		getline(cin,line);
		if(line=="$") break;
		string description= line.size()>14 ? line.substr(14) : "";
		long phone=atol(line.substr(0,8).c_str());
		int internalCode=atoi(line.substr(8,3).c_str());
		int amount=atoi(line.substr(12,1).c_str());
		int restaurantID=findRestaurant(phone,restaurants);
		int foodID=restaurants[restaurantID].findFood(internalCode); 
		if(restaurantID==-1||foodID==-1) return false;
		currentOrder.addItem(restaurantID,foodID,amount,description);
	}
	orders.push_back(currentOrder);
	return true;
} 