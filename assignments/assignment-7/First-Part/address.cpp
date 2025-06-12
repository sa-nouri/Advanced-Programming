#include "address.h"
using namespace std;
Universe Address::universe;
Address::Address(string str){
	if(str=="DEFAULT"){galaxy=NULL;planet=NULL;return;}
	galaxy=universe.findGalaxy(str.substr(0,str.find(',')));
	if(!galaxy)
		throw BadAddress();
	planet=galaxy->findPlanet(str.substr(str.find(',')+1));
	if(!planet)
		throw BadAddress();

}

int Address::distanceWith(const Address& arg)const{
	if(galaxy==arg.galaxy)
		return planet->distance(arg.planet);
	return planet->distance(galaxy->gatedPlanet())+
	arg.planet->distance(arg.galaxy->gatedPlanet())+1;
}

 std::string Address::toStr(){
 	return galaxy->getName()+','+planet->getName();
 }