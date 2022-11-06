#include "space_ship.h"
SpaceShipGallery SpaceShip::gallery;
using namespace std;

SpaceShip::SpaceShip(long _num,string _model,string year,string _color){
	if(!gallery.foundModel(_model)) 
		throw ModelNotFound(_model);
	number=_num;
	model=_model;
	productYear=year;
	color=_color;
}
long SpaceShip::getNumber()const{
	return number;
}
string SpaceShip::getModel()const{
	return model;
}
std::string SpaceShip::getProductYear()const{
	return productYear;
}
std::string SpaceShip::getColor()const{
	return color;
}