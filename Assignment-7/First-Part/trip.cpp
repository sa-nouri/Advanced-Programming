#include "trip.h"

Trip::Trip(const DateTime& _date,Passenger* _passenger,bool _VIP): date(_date){
	
	currentTime=&date;
	VIP=_VIP;
	done=false;
	driverPayed=false;
	rate=0;
	passenger=_passenger;
	driver=NULL;
	cost=0;
}

void Trip::addLandmark(const Address& toAdd){
	landmarks.push_back(toAdd);
}
DateTime Trip::getDate (){
	return date;
}
int Trip::calcCost(){
	double coeficient=1;
	if(VIP) coeficient=2; 
	if(passenger->isJournier(currentTime)) coeficient=0.5; 
	return coeficient*distance();
}
int Trip::distance(){

	int result=0;
	for (int i = 0; i < landmarks.size()-1; ++i)
		result+=landmarks[i].distanceWith(landmarks[i+1]);	
	return result;
}
int Trip::getRate(){
	return rate;
}

Address Trip::getSource(){
	return landmarks[0];
}
std::string Trip::getLandmarks(){
	std::string result;
	for (int i = 0; i < landmarks.size(); ++i){
		result+=" "+landmarks[i].toStr();
	}
	result.erase(result.begin());
	return result;
}
Passenger* Trip::getPassenger(){
	return passenger;
}


Driver* Trip::getDriver(){
	return driver;
}

void Trip::setDriver(Driver* _driver){
	driver=_driver;
}

void Trip::setRate (int _rate){
	if(_rate>10||_rate<1) throw "Bad rate.";
	rate=_rate;
}
Address Trip::getDestination(){
	return landmarks.back();
}


int Trip::getCost(){return cost;}
void Trip::setCost(){cost=calcCost();}