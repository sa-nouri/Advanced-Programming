#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"
#include <vector>
#include <string>
#include "trip.h"
#include "space_ship.h"
#include "address.h"
#include "date_time.h"
class Trip;
class Driver :public User {
public:
	~Driver();
	SpaceShip getSpaceShip();
	Driver(std::string,std::string,long,std::string,std::string,std::string,bool,const DateTime&);
	int calcSalary();
	Address getAddress();
	void setAddress(std::string);
	void addCredit(int);
	std::string getStatus();
	void setStatus(std::string state);
	void addRequest(Trip* trip);
	void removeRequest(Trip* trip);
	std::vector<Trip*> getRequests();
	std::vector<Trip*> getTrips();
	DateTime getRegistrationDate();
	void addToTrips(Trip* trip);
	int getRate();
	int endTrip();
	bool arrive();

	bool VIP;
	bool accepted;
	bool arrived;
	
private:
	DateTime registrationDate;
	std::string status;
	int credit;
	std::vector<Trip*>  trips;
	SpaceShip spaceShip;
	Address address;
	std::vector<Trip*> requests;
};
#endif