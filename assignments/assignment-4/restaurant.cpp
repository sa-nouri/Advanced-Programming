#include "restaurant.h"
Restaurant::Restaurant(string _name,long _phone,string _region){
	if(_name.size()==0 || _phone<10000000 || _region.size()==0)
		abort();
	name=_name;
	phone=_phone;
	region=_region;
}
void insertFood(vector<Food>& listOfFoods,Food toAdd){
	if (listOfFoods.size() == 0){
		listOfFoods.push_back(toAdd) ;
		return ;
	}
	else if( toAdd.getCode() <= listOfFoods[0].getCode()){
		listOfFoods.insert(listOfFoods.begin(),toAdd);
		return ;
	}
	else{
		Food firstItem (listOfFoods[0]);
		listOfFoods.erase(listOfFoods.begin());
		insertFood(listOfFoods,toAdd);
		listOfFoods.insert(listOfFoods.begin(),firstItem);
	}
}
void Restaurant::addFood(int internalCode,string name,FoodType type,int cost){
	insertFood(listOfFoods,Food(phone*1000+internalCode,name,type,cost));
}
vector<Food> Restaurant::listFoodsOfCategory(FoodType _type){
	vector<Food> result;
	for(int i=0;i<listOfFoods.size();i++)
		if(listOfFoods[i].getType()==_type)
			result.push_back(listOfFoods[i]);
	return result;
}
