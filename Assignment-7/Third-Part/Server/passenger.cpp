#include "passenger.h"
using namespace std;
long Passenger::getPhone(){
	return phoneNumber;
}
Passenger::Passenger(string userName,string password,long phone,const DateTime& regDate)
:User(userName,password),registrationDate(regDate){
	phoneNumber=phone;
	availableCount=0;
	credit=0;
}
int Passenger::getAvailableCount(){
	return availableCount;
}
void Passenger::setAvailableCount(int cnt){
	availableCount=cnt;
}

void Passenger::addCredit (int plus){

	credit+=plus;
}

void Passenger::addTrip(Trip* toAdd){

	lastTrips.push_back(toAdd);
	if(lastTrips.size()>3)
		lastTrips.erase(lastTrips.begin());
}
bool Passenger::isJournier (DateTime* current){


	if(lastTrips.size()<3)
		return false;
	
	if(DateTime("2-0:0:0")<(*current)-lastTrips[2]->getDate())
		return false;
	return (lastTrips[2]->getDate()-lastTrips[1]->getDate())+(lastTrips[1]->getDate()-lastTrips[0]->getDate())<
	DateTime("1-0:0:0");
}
int Passenger::getCredit()const{
	return credit;
}
Trip* Passenger::getLastTrip(){
	if(!lastTrips.size()) return NULL;
	return lastTrips.back();
}
void Passenger::removeLastTrip(){
	lastTrips.pop_back();
}
DateTime Passenger::getRegistrationDate(){
	return registrationDate;
}