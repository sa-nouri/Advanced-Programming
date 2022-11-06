#include "order.h"
costStatus Order::calculateTotalCost(string customerRegion,vector<Restaurant>& restaurants){
	bool ignoreDelivery=true;
	int totalPrice=0;
	for(int i=0;i<orderItems.size();i++){
		Food currentRecord=restaurants[orderItems[i].getRestaurantIndex()].listAllFoods()[orderItems[i].getFoodIndex()];
		totalPrice+=currentRecord.getCost()*orderItems[i].getAmount();

		if(restaurants[orderItems[i].getRestaurantIndex()].getRegion()!=customerRegion){
			ignoreDelivery=false;
		}
	}
	if(totalPrice>100000)
		ignoreDelivery=true;

	if(!ignoreDelivery)
		totalPrice+=5000;
	return costStatus(ignoreDelivery,totalPrice);
}

