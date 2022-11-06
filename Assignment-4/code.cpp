
#include "food.h"
#include "customer.h"       
#include "restaurant.h"
#include "order.h"
#include "order_item.h"

FoodType findType(string str){
	if(str=="European")
		return European;
	if(str=="Iranian")
		return Iranian;
	if(str=="Eastern")
		return Eastern;	
	return -1;
}

bool loadCustomersInfo(vector<Customer>& customers){
	ifstream file ("customers.txt");
	if (!file.is_open())
		return false;
	string line;
	bool newRestaurant=true; 
	while (getline(file,line)){
		string::size_type firstDelim,secondDelim;
		firstDelim=line.find(',');
		secondDelim=line.find(',',firstDelim+1);
		string name=line.substr(0,firstDelim);
		long phone=atol(line.substr(firstDelim+1,secondDelim-firstDelim-1).c_str());
		string region=line.substr(secondDelim+1);
		customers.push_back(Customer(name,phone,region));	
	}
	file.close();
	return true;
}

void insertResturant(vector<Restaurant>& restaurants,Restaurant toAdd,int& wherePushed){
	if (restaurants.size() == 0){
		restaurants.push_back(toAdd) ;
		return ;
	}
	else if( toAdd.getPhone() <= restaurants[0].getPhone()){
		restaurants.insert(restaurants.begin(),toAdd);
		return ;
	}
	else{
		Restaurant firstItem (restaurants[0]);
		restaurants.erase(restaurants.begin());
		insertResturant(restaurants,toAdd,++wherePushed);
		restaurants.insert(restaurants.begin(),firstItem);
	}
}
bool loadRestaurantsInfo(vector<Restaurant>& restaurants){
	ifstream file ("restaurants.txt");
	if (!file.is_open())
		return false;
	string line;
	bool newRestaurant=true; 
	int wherePushed=0;
	while (getline(file,line)){
		if(newRestaurant){
			string::size_type firstDelim,secondDelim;
			firstDelim=line.find(',');
			secondDelim=line.find(',',firstDelim+1);
			string name=line.substr(0,firstDelim);
			long phone=atol(line.substr(firstDelim+1,secondDelim-firstDelim-1).c_str());
			string region=line.substr(secondDelim+1);
			wherePushed=0;
			insertResturant(restaurants,(Restaurant(name,phone,region)),wherePushed);
			newRestaurant=false;
		}
		else{
			if(line.size()==0){
				newRestaurant=true;
				continue;
			}

			string::size_type firstDelim,secondDelim,thirdDelim;
			firstDelim=line.find(',');
			secondDelim=line.find(',',firstDelim+1);
			thirdDelim=line.find(',',secondDelim+1);
			int internalCode=atoi(line.substr(0,firstDelim).c_str());
			string name=line.substr(firstDelim+1,secondDelim-firstDelim-1);
			FoodType type= findType(line.substr(secondDelim+1,thirdDelim-secondDelim-1));
			int cost=atoi(line.substr(thirdDelim+1).c_str());
			restaurants[wherePushed].addFood(internalCode,name,type,cost);
		}
	}
	file.close();
	return true;
}

string convertFoodTypeToStr(FoodType type){
	if(type==Iranian)
		return "Iranian";
	if(type==European)
		return "European";
	if(type==Eastern)
		return "Eastern";
	return "";
}

bool printMenu(long phone, vector<Restaurant>& restaurants ){
	for(int i=0;restaurants.size();i++){
		if(restaurants[i].getPhone()==phone){
			for(int j=0;j<restaurants[i].listAllFoods().size();j++){
				vector<Food> foods=restaurants[i].listAllFoods();
				cout<<foods[j].getCode()<<' '<<foods[j].getName()<<' '<<
				convertFoodTypeToStr(foods[j].getType())<<' '<<foods[j].getCost()<<endl;
			}
			return true;
		}
	}
	return false;
}
struct printSuccession{
	bool usrFound;
	bool restaurantFound;
	printSuccession(bool usrFound,bool restaurantFound):usrFound(usrFound),restaurantFound(restaurantFound){};
};
int findUser(long phone,vector<Customer>& customers){
	for(int i=0;i<customers.size();i++)
		if(customers[i].getPhone()==phone)
			return i;
	return -1;
}
printSuccession PrintRestaurants(vector<Customer>& customers,vector<Restaurant>& restaurants,long usrPhone=-1){
	bool usrFound=false;
	bool restaurantFound=false;
	int customerIndex;
	if(usrPhone!=-1){
		customerIndex=findUser(usrPhone,customers);
		if(customerIndex==-1) return printSuccession(false,true);
	}
	else usrFound=true;
	for(int i=0;i<restaurants.size();i++){
		if(usrPhone==-1){
			restaurantFound=true;
			cout<<restaurants[i].getName()<<' '<<restaurants[i].getRegion()<<' '<<restaurants[i].getPhone()<<endl;
		}
		else if(customers[customerIndex].getRegion()==restaurants[i].getRegion()){
			cout<<restaurants[i].getName()<<' '<<restaurants[i].getRegion()<<' '<<restaurants[i].getPhone()<<endl;
			restaurantFound=true;			
		}
	}
	printSuccession result(usrFound,restaurantFound);
	return result;
}
bool listType(string _type,vector<Restaurant>& restaurants){
	bool result=false;
	FoodType type= findType(_type);
	if(type==-1)
		return false;
	for(int i=0;i<restaurants.size();i++){
		vector<Food> list=restaurants[i].listFoodsOfCategory(type);
		for(int j=0;j<list.size();j++){
			result=true;
			cout<<list[j].getCode()<<' '<<list[j].getName()<<' '<<_type<<' '<<list[j].getCost()
			<<' '<<restaurants[i].getName()<<' '<<restaurants[i].getRegion()<<endl;
		}
	}
	return false;
}
printSuccession listNear(vector<Customer>& customers,vector<Restaurant>& restaurants,long usrPhone){
	bool usrFound=false;
	bool restaurantFound=false;
	int customerIndex;
	customerIndex=findUser(usrPhone,customers);
	if(customerIndex==-1) return printSuccession(false,true);
	for(int i=0;i<restaurants.size();i++){
		if(customers[customerIndex].getRegion()==restaurants[i].getRegion()){
			vector<Food> list= restaurants[i].listAllFoods();
			for(int j=0;j<list.size();j++)
				cout<<list[j].getCode()<<' '<<list[j].getName()<<' '<<convertFoodTypeToStr(list[j].getType())<<' '<<list[j].getCost()
				<<' '<<restaurants[i].getName()<<' '<<restaurants[i].getRegion()<<endl;
			restaurantFound=true;			
		}
	}
	printSuccession result(usrFound,restaurantFound);
	return result;	
}
printSuccession handleOrder(long usrPhone,vector<Customer>&customers,vector<Restaurant>&restaurants){
	int customerIndex=findUser(usrPhone,customers);
	if(customerIndex==-1) return printSuccession(false,true);
	bool restaurantFound=customers[customerIndex].readOrder(restaurants);
	cout<<customers[customerIndex].getName()<<' '<<usrPhone<<' '<<
	customers[customerIndex].getOrders().back().calculateTotalCost(customers[customerIndex].getRegion(),restaurants).totalPrice<<endl;
	return printSuccession(true,restaurantFound);
}
bool printBill(long usrPhone,vector<Customer>&customers,vector<Restaurant>&restaurants){
	int customerIndex=findUser(usrPhone,customers);
	if(customerIndex==-1) return false;
	cout<<customers[customerIndex].getName()<<' '<<usrPhone<<' '<<endl;
	if(customers[customerIndex].getOrders().size()==0) return true;
	vector<OrderItem> lastBill=customers[customerIndex].getOrders().back().getOrderItems();
	for(int i=0;i<lastBill.size();i++){
		Food ithFood=restaurants[lastBill[i].getRestaurantIndex()].listAllFoods()[lastBill[i].getFoodIndex()];
		cout<<ithFood.getCode()<<' '<< ithFood.getName()<<' '<<convertFoodTypeToStr(ithFood.getType()) <<
		' '<< ithFood.getCost()<<' '<<lastBill[i].getAmount()<<' '<<ithFood.getCost()*lastBill[i].getAmount()<<' '<<lastBill[i].getDescription()<<endl;
	}
	costStatus totalCost= customers[customerIndex].getOrders().back().calculateTotalCost(customers[customerIndex].getRegion(),restaurants);
	cout<<"delivery cost ";
	if(totalCost.ignoreDelivery)
		cout<<0<<endl;
	 else 
	 	cout<<5000<<endl;
	 cout<<"total cost "<<totalCost.totalPrice<<endl;
	return true;
}
bool printBillAll(long usrPhone,vector<Customer>&customers,vector<Restaurant>&restaurants){
	int customerIndex=findUser(usrPhone,customers);
	if(customerIndex==-1) return false;
	cout<<customers[customerIndex].getName()<<' '<<usrPhone<<' '<<endl;
	if(customers[customerIndex].getOrders().size()==0) return true;
	int totalPurchase=0;
	for(int j=0;j<customers[customerIndex].getOrders().size();j++){
		vector<OrderItem> jthBill=customers[customerIndex].getOrders()[j].getOrderItems();
		for(int i=0;i<jthBill.size();i++){
			Food ithFood=restaurants[jthBill[i].getRestaurantIndex()].listAllFoods()[jthBill[i].getFoodIndex()];
			cout<<ithFood.getCode()<<' '<< ithFood.getName()<<' '<<convertFoodTypeToStr(ithFood.getType()) <<
			' '<< ithFood.getCost()<<' '<<jthBill[i].getAmount()<<' '<<ithFood.getCost()*jthBill[i].getAmount()<<' '<<jthBill[i].getDescription()<<endl;
		}
		costStatus totalCost= customers[customerIndex].getOrders()[j].calculateTotalCost(customers[customerIndex].getRegion(),restaurants);
		cout<<"delivery cost ";
		if(totalCost.ignoreDelivery)
			cout<<0<<endl;
		 else 
		 	cout<<5000<<endl;
		 cout<<"total cost "<<totalCost.totalPrice<<endl<<'#'<<endl;
		 totalPurchase+=totalCost.totalPrice;
	}
	cout<<"total purchase "<<totalPurchase<<endl;


	return true;
}



vector<string> readCmd(){
	string str;
	vector<string> result;
	if(!getline(cin,str)) return result;
	int prevDelim=-1;
	for(int i=0;i<str.size();i++)
		if(str[i]==' '){
			result.push_back(str.substr(prevDelim+1,i-prevDelim-1));
			prevDelim=i;
		}
		result.push_back(str.substr(prevDelim+1));
	return result;
}


int main(){
	vector<Restaurant> restaurants;
	vector<Customer> customers;
	loadRestaurantsInfo(restaurants);
	loadCustomersInfo(customers);
	while(true){
		vector<string> args=readCmd();
		if(args.size()==0)
			 break;
		if(args.size()==1){
			if(args[0]=="restaurants")
				PrintRestaurants(customers,restaurants);
		}
		else if(args.size()==2){
			if(args[0]=="menu")
				printMenu(atol(args[1].c_str()),restaurants);
			if(args[0]=="order")
				handleOrder(atol(args[1].c_str()),customers,restaurants);
			if(args[0]=="bill")
				printBill(atol(args[1].c_str()),customers,restaurants);
		}
		else if(args.size()==3){
			if(args[0]=="restaurants" && args[1]=="near")
				PrintRestaurants(customers,restaurants,atol(args[2].c_str()));
			if(args[0]=="list" && args[1]=="near")
				listNear(customers,restaurants,atol(args[2].c_str()));
			if(args[0]=="list" && args[1]=="type")
				listType(args[2],restaurants);
			if(args[0]=="bill" && args[1]=="all")
				printBillAll(atol(args[2].c_str()),customers,restaurants);


		}
	}

	return 0;
}
