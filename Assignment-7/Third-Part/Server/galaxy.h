#ifndef GALAXY_H
#define GALAXY_H
#include <iostream>
#include <stdlib.h>
#include "planet.h"
#include <vector>
#include <fstream>
class Galaxy{
public:
	Galaxy(std::ifstream& filePtr);
	Planet* findPlanet(std::string key);
	Planet* gatedPlanet();
	std::string getName();
	~Galaxy();
private:
	std::vector<Planet*> planets;
	std::string name;
	
};
#endif