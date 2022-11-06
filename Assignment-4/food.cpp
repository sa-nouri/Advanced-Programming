#include "food.h"

using namespace std;

Food::Food(long _code,string _name,FoodType _type,int _cost){
	
	if((_type!=Iranian&&_type!=Eastern&&_type!=European)||_code<10000000000||_name.size()==0||_cost<0)
		abort();
	code=_code;
	name=_name;
	type=_type;
	cost=_cost;
}