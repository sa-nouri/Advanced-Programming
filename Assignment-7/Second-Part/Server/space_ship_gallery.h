#ifndef SPACE_SHIP_GALLARY_H
# define SPACE_SHIP_GALLARY_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "reading_file_err.h"

class SpaceShipGallery{
public:
	SpaceShipGallery();
	bool foundModel(std::string)const;
private:
	std::vector<std::string> models;
	
};
#endif