#ifndef TRIP_H
#define TRIP_H
#include <vector>
#include <string>
#include "driver.h"
#include "address.h"
#include "passenger.h"
#include "date_time.h"
class Driver;
class Passenger;
class Trip {
public:
	Trip(const DateTime& date,Passenger* _passenger,bool _VIP);
	void setDriver(Driver* driver);
	void addLandmark(const Address& toAdd);
	Address getSource();
	Address getDestination();
	std::string getLandmarks();
	
	int getCost();
	void setCost();
	void setRate (int);
	int getRate ();
	DateTime getDate ();
	int distance ();
	Passenger* getPassenger();
	Driver* getDriver();
	bool VIP;
	bool done;
	bool driverPayed;
private:
	DateTime* currentTime;
	int rate;
	DateTime date;
	std::vector<Address> landmarks;
	Passenger* passenger;
	Driver* driver;
	int cost;
	int calcCost();
};

#endif