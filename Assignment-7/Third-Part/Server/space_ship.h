#ifndef SPACE_SHIP
#define SPACE_SHIP
#include "space_ship_gallery.h"
#include "model_not_found.h"
#include <string>
class SpaceShip {
public:
	SpaceShip(long _num,std::string _model,std::string year,
		std::string _color);
public:
	long getNumber()const;
	std::string getModel()const;
	std::string getProductYear()const;
	std::string getColor()const;
private:
	long number;
	std::string model;
	std::string productYear;
	std::string color;
	static SpaceShipGallery gallery;
};
#endif