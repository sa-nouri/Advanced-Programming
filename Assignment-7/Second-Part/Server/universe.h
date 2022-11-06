#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "galaxy.h"
#include <vector>
#include <string>
#include "reading_file_err.h"
class Universe 
{
public:

	Universe();
	~Universe();
	Galaxy* findGalaxy(std::string);
	//int distance (Address,Address);
private:
	std::vector<Galaxy*> galaxies;
};
#endif