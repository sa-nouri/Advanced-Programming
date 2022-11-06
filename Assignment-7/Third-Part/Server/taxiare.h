#ifndef TAXIARE
#define TAXIARE
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
#include "server.h"
#include <map>

class Taxiare:public Server {
public:
	Taxiare(int port);
	~Taxiare();
	std::string getRequest(std::string);

//------------------------------------------------------------------
	void on_standard_input(std::string line);
	void on_new_connection(int identifier);
	void on_new_message(int identifier, std::string message);
	void on_terminated_connection(int identifier);

private:
	int credit;
	std::vector<Driver*> drivers;
	std::vector<Passenger*> passengers;
	DateTime calendar;
	std::vector<User*> loggedInUsers;
	Admin admin;
	std::map <std::string, int> connectedUsers;

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
	std::map<std::string, int>::iterator serachByIdentity(int identity);

};
#endif
