#include "space_ship_gallery.h"
using namespace std;
SpaceShipGallery::SpaceShipGallery(){
	ifstream filePtr ("vehicles.cfg");
	if(!filePtr.is_open()) throw readingFileErr("vehicles.cfg");
	string line;
	while(getline(filePtr,line))
		models.push_back(line);
}
bool SpaceShipGallery::foundModel(std::string key)const{
	for(int i=0;i<models.size();i++)
		if(models[i]==key)
			return true;
	return false;
}