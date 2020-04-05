#ifndef SERVER
#define SERVER
#include <vector>
#include <string>
#include <stdlib.h> 
#include <sstream>
#include <algorithm>
#include "date_time.h"
#include "passenger.h"
#include "driver.h"
#include "date_time.h"
#include "user.h"
#include "admin.h"
class Server {
public:
	Server();
	~Server();
	std::string getRequest(std::string);
private:
	int credit;
	std::vector<Driver*> drivers;
	std::vector<Passenger*> passengers;
	DateTime calendar;
	std::vector<User*> loggedInUsers;
	Admin admin;

	std::vector<std::string> parseCommand(std::string);
	std::string registerPassenger(std::string,std::string,std::string,std::string);
	std::string registerDriver(const std::vector<std::string>&);
	std::string acceptRejectRegistration(std::string driverUserName,bool accept);
	std::string showRegistrationRequests();
	std::string getDiscountCode(Passenger* passenger );
	std::string login(std::string ,std::string);
	std::string logout(User*);
	std::string	setStatus(Driver*, std::string, std::string);
	std::string estimateTrip(const std::vector<std::string>&);
	std::string requestTrip(const std::vector<std::string>& command);
	std::string cancelTrip(Passenger*);
	std::string showTripRequests(Driver*);
	std::string acceptTripRequest(Driver*,std::string);
	std::string tripStatus(Passenger*);
	std::string setTime(std::string);
	std::string driverReport(std::string,std::string,std::string);
	std::string passengerReport(std::string);
	std::string systemReport(std::string,std::string);
//__________________________________________________________________________________
	void removeFromDriversRequests(Trip* trip);
	bool addToDriversRequests(Trip* trip);
	Passenger* findPassenger(std::string userName);
	Driver* findDriver(std::string userName);
	User* findCommandingUser(std::string);
};
#endif
