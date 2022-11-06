#include "universe.h"
using namespace std;

Universe::Universe(){
	std::ifstream filePtr ("topology.cfg");
	if(!filePtr.is_open()) throw readingFileErr("topology.cfg");
	std::string line;
	getline(filePtr,line);
	int numOfGalaxies=atoi(line.c_str());
	for(int i=0;i<numOfGalaxies;i++)
		galaxies.push_back(new Galaxy(filePtr));
}
Universe::~Universe(){
	for(int i=0;i<galaxies.size();i++)
		delete galaxies[i];
}
Galaxy* Universe::findGalaxy(std::string key){
	for(int i=0;i<galaxies.size();i++)
		if(galaxies[i]->getName()==key)
			return galaxies[i];
	return NULL;
}