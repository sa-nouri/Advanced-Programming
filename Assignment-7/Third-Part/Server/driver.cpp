#include "driver.h"
using namespace std;
Driver::Driver(std::string userName,std::string password,long number,std::string model,std::string year,
	std::string color,bool _VIP,const DateTime& regDate):User(userName,password),
spaceShip(number,model,year,color),address("DEFAULT"),registrationDate(regDate){
	VIP=_VIP; 
	credit=0;
	accepted=false;
	status="unavailable";
	arrived=false;
}
SpaceShip Driver::getSpaceShip(){
	return spaceShip;
}
std::string Driver::getStatus(){
	return status;
}
void Driver::setStatus(std::string state){

	if(state!="unavailable"&&state!="available"&&state!="triping") 
		throw "Bad state is set.";
	status=state;

}
Address Driver::getAddress(){
	return address;
}
void Driver::setAddress(string _address){
	address=Address(_address);
}
int Driver::getRate(){
	int result=0;
	for (int i = 0; i < trips.size(); i++)
		result+=trips[i]->getRate();
	return result;
}


void Driver::addRequest(Trip* trip){
	requests.push_back(trip);
}
void Driver::removeRequest(Trip* trip){
	for (int i = 0; i < requests.size(); ++i){
		if(requests[i]==trip){
			requests.erase(requests.begin()+i);

		}
	}
}
std::vector<Trip*> Driver::getRequests(){
	return requests;
}

bool Driver::arrive(){

	if(!trips.size()) return false;
	if(trips.back()->done) return false;
	
	address=trips.back()->getSource();
	arrived=true;
	return true;
		
}

void Driver::addToTrips(Trip* trip){
	trips.push_back(trip);
}

int Driver::endTrip(){
	
	if(!trips.size()) return 0;
	if(trips.back()->done) return 0;

	address=trips.back()->getDestination();
	status="available";
	trips.back()->getPassenger()->addCredit(-1*trips.back()->getCost());
	trips.back()->done=true;
	return trips.back()->getCost();
}
int Driver::calcSalary(){
	int result=0;
	for (int i = 0; i < trips.size(); i++){
		if(trips[i]->done&&!trips[i]->driverPayed){
			result+=trips[i]->getCost();
			trips[i]->driverPayed=true;
		}
	}
	return result;
}
void Driver::addCredit(int add){
	credit+=add;
}
std::vector<Trip*> Driver::getTrips(){
	return trips;
}
DateTime Driver::getRegistrationDate(){
	return registrationDate;
}
Driver::~Driver(){
	for (int i = 0; i < trips.size(); ++i)
		delete trips[i];
}