#include "planet.h"
#include <iostream>
using namespace std;
Planet::Planet(std::string _name){
	name=_name;
}
std::string Planet::getName(){
	return name;
}
void Planet::addNeighbor( Planet* toAdd){
	neighbors.push_back(toAdd);
}
bool Planet::recursiveDistance (Planet* key,Planet* parent,int& distance){

	if(this==key)
		return true;
	distance++;
	
	for(int i=0;i<neighbors.size();i++)
		if(neighbors[i]!=parent)
			if(neighbors[i]->recursiveDistance(key,this,distance))
				return true;
	
	distance--;
	return false;
}
int Planet::distance (Planet* key){
	int distance=0;
	this->recursiveDistance(key,NULL,distance);
	return distance;
}