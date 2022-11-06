#ifndef PLANET_H
#define PLANET_H
#include <string>
#include <vector>
class Planet {
public:
	Planet(std::string);
	std::string getName ();
	void addNeighbor(Planet*);
	int distance (Planet*);
private:
	bool recursiveDistance (Planet*,Planet*,int& distance);
	std::vector<Planet*> neighbors;
	std::string name;
};
#endif