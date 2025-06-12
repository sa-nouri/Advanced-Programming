#ifndef PASSENGER_H
#define PASSENGER_H
#include "user.h"
#include <vector>
#include <string>
#include "date_time.h"
#include "trip.h"
class Trip;
class Passenger :public User {
public:
	Passenger(std::string,std::string,long,const DateTime&);
	long getPhone();
	bool isJournier (DateTime*);
	void addCredit (int );
	int getAvailableCount();
	void setAvailableCount(int);
	void addTrip(Trip* toAdd);
	Trip* getLastTrip();
	void removeLastTrip();
	int getCredit()const;
	DateTime getRegistrationDate();
private:
	int credit;
	std::vector<Trip*> lastTrips;
	long phoneNumber;
	int availableCount;
	DateTime registrationDate;
};
#endif
