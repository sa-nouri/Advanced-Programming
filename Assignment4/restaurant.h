#ifndef RESTAURANT_H
#define RESTAURANT_H
#include "food.h"
#include "includes.h"
class Restaurant{
public:
	Restaurant (string _name,long _phone,string _region);
	string getName(){return name;};
	long getPhone(){return phone;};
	string getRegion(){return region;};
	vector<Food> listAllFoods(){return listOfFoods;};
	vector<Food> listFoodsOfCategory(FoodType _type);
	void addFood(int internalCode,string name,FoodType type,int cost);
	int findFood(int internalCode){
		for(int i=0;i<listOfFoods.size();i++)
			if(listOfFoods[i].getCode()%1000==internalCode)
				return i;
		return -1;
	}
private:
	string name;
	string region;
	long phone;
	vector<Food> listOfFoods;
};

#endif
