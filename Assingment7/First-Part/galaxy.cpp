#include "galaxy.h"
using namespace std;

Planet* Galaxy::findPlanet(string key){
	for(int i=0;i<planets.size();i++){
		if(planets[i]->getName()==key){
			return planets[i];
		}
	}
	return NULL;
}
int devideStr(string& str){
	int result=atoi(str.substr(str.find(' ')+1).c_str());
	str=str.substr(0,str.find(' '));
	return result;
}

Galaxy::Galaxy(ifstream& filePtr){
	string line;
	getline(filePtr,line);
	int numOfPlanets=devideStr(line);
	name=line;
	for(int i=0;i<numOfPlanets;i++){
		getline(filePtr,line);
		int numOfChildren=devideStr(line);
		string currentPlanetName=line;
		Planet* currentPlanetAddress=findPlanet(line);
		if(!currentPlanetAddress){
			currentPlanetAddress=new Planet(line);
			planets.push_back(currentPlanetAddress);
		}
		//By here currentPlanetAddress is generated.
		for(int j=0;j<numOfChildren;j++){
			getline(filePtr,line);
			Planet* childAddress=findPlanet(line);
			if(!childAddress){
				childAddress=new Planet(line);
				planets.push_back(childAddress);
			}
			//By here childAddress is generated.
			currentPlanetAddress->addNeighbor(childAddress);

		}
	}
}
Planet* Galaxy::gatedPlanet(){return planets[0];}
Galaxy::~Galaxy(){
	for(int i=0;i<planets.size();i++)
		delete planets[i];
}
std::string Galaxy::getName(){
	return name;
}