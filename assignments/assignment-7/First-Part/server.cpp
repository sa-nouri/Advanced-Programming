#include "server.h"
using namespace std;
Server::Server():admin("admin","s3cret"),calendar("1-0:0:0"){
	credit=0;
}
template <typename T>
string ntoa(T l){
	std::string result;
	std::stringstream strstream;
	strstream << l;
	strstream >>result;
	return result;
}
string Server::getRequest(string cmd){
	vector<string>command=parseCommand(cmd);
	if(command.size()<2) return "Bad arguments.";
	if(command[1]=="register_passenger"){
		if(command.size()!=4&&command.size()!=5) 
			return "Bad arguments.";
		string cmd4=command.size()==5 ? command[4] : "";
		return registerPassenger(command[0],command[2],command[3],cmd4);
	}

	if(command[1]=="register_driver"){
		if(command.size()!=8 && command.size()!=7)  
			return "Bad arguments.";
		return registerDriver(command);
	}

	if(command[1]=="login"){
		if(command.size()!=3)
			return "Bad arguments.";
		return login(command[0],command[2]);
	}

	User* commandingUser=findCommandingUser(command[0]);
	if(!commandingUser)
		return command[0]+" hasn't logged in.";
//// By then Login is required.
	if(command[1]=="accept_registration"||command[1]=="reject_registration"){
		if(command.size()!=3||command[0]!="admin") 
			return "Bad arguments.";
		return acceptRejectRegistration(command[2],command[1]=="accept_registration");

	}

	if(command[1]=="show_registration_requests"){
		if(command.size()!=2||command[0]!="admin") 
			return "Bad arguments.";
		return showRegistrationRequests();
	}

	if(command[1]=="set_time"){
		if(command.size()!=3||command[0]!="admin") 
			return "Bad arguments.";
		return setTime(command[2]);
	}

	if(command[1]=="driver_report"){
		if(command.size()!=5||command[0]!="admin") 
			return "Bad arguments.";
		return driverReport(command[2],command[3],command[4]);
	}

	if(command[1]=="passenger_report"){
		if(command.size()!=3||command[0]!="admin") 
			return "Bad arguments.";
		return passengerReport(command[2]);
	}
	if(command[1]=="system_report"){
		if((command.size()!=2&&command.size()!=4)||command[0]!="admin") 
			return "Bad arguments.";
		string arg2= command.size()==2 ? "0-0:0:0" : command[2];
		string arg3= command.size()==2 ? "999999-0:0:0" : command[3];
		return systemReport(arg2,arg3);
	}
	if(command[1]=="get_discount_code"){
		if(command.size()!=2) 
			return "Bad arguments.";
		return getDiscountCode((Passenger*)commandingUser);
	}

	if(command[1]=="logout"){
		if(command.size()!=2)
			return "Bad arguments.";
		return logout(commandingUser);
	}
	if(command[1]=="set_status"){
		if(command.size()!=3&&command.size()!=4)
			return "Bad arguments.";
		string addr=command.size()==3 ? "" : command[3];
		return setStatus((Driver*)commandingUser,command[2],addr);
	}
	if(command[1]=="estimate_trip"){
		if(command.size()<4)
			return "Bad arguments.";
		return estimateTrip(command);
	}
	if(command[1]=="request_trip"){
		if(command.size()<4)
			return "Bad arguments.";
		return requestTrip(command);
	}
	if(command[1]=="cancel_trip_request"){
		if(command.size()!=2)
			return "Bad arguments.";
		return cancelTrip((Passenger*)commandingUser);
	}	
	if(command[1]=="show_trip_requests"){
		if(command.size()!=2)
			return "Bad arguments.";
		return showTripRequests((Driver*)commandingUser);
	}
	if(command[1]=="accept_trip_request"){
		if(command.size()!=3)
			return "Bad arguments.";
		return acceptTripRequest((Driver*)commandingUser,command[2]);
	}
	if(command[1]=="trip_status"){
		if(command.size()!=2)
			return "Bad arguments.";
		return tripStatus((Passenger*)commandingUser);
	}
	if(command[1]=="arrived"){
		if(command.size()!=2)
			return "Bad arguments.";
		if(!((Driver*)commandingUser)->arrive()) 
			return((Driver*)commandingUser)->getName()+" doesn't have undone trips.";
		return "";
	}
	if(command[1]=="end_trip"){
		if(command.size()!=2)
			return "Bad arguments.";
		int income=((Driver*)commandingUser)->endTrip(); 
		if(!income)
			return((Driver*)commandingUser)->getName()+" doesn't have undone trips.";
		credit+=income;
		return "";
	}					
	if(command[1]=="rate_driver"){
		if(command.size()!=3)
			return "Bad arguments.";
		if(atoi(command[2].c_str())>10||atoi(command[2].c_str())<1) 
			return "Invalid value for rate.";
		((Passenger*)commandingUser)->getLastTrip()->setRate(atoi(command[2].c_str()));
		return "";
	}
	if(command[1]=="charge_account"){
		if(command.size()!=3)
			return "Bad arguments.";
		if(atoi(command[2].c_str())<0) 
			return "Invalid value for amount.";
		((Passenger*)commandingUser)->addCredit(atoi(command[2].c_str()));
		return "";
	}
	if(command[1]=="get_credit"){
		if(command.size()!=2)
			return "Bad arguments.";
		return ntoa(((Passenger*)commandingUser)->getCredit());
	}	

	return "Unknown command.";	
}

Driver* Server::findDriver(string userName){
	for (int i = 0; i < drivers.size(); i++){
		if(drivers[i]->getName()==userName)
			return drivers[i];
	}
	return NULL;
}

Passenger* Server::findPassenger(string userName){
	for (int i = 0; i < passengers.size(); i++){
		if(passengers[i]->getName()==userName)
			return passengers[i];
	}
	return NULL;
}

User* Server::findCommandingUser(std::string userName){
	for (int i = 0; i < loggedInUsers.size(); ++i){
		if(loggedInUsers[i]->getName()==userName)
			return loggedInUsers[i];
	}
	return NULL;
}
vector<string> Server::parseCommand(string cmd){
	vector<string> result;
	size_t delim=cmd.find(' ');
	while(delim!=string::npos){
		result.push_back(cmd.substr(0,delim));
		cmd=cmd.substr(delim+1);
		delim=cmd.find(' ');
	}
	result.push_back(cmd);
	return result;	
}

string Server::registerPassenger(string userName,string password,string phone,string code){

	bool plus10=false;
	if(code!="") {
		Passenger* inviter=NULL;
		for (int i = 0; i < passengers.size(); i++){
			if((long)passengers[i]==atol(code.c_str()))
				inviter=passengers[i];
		}
		if(!inviter) return "Invalid code.";
		if(!inviter->getAvailableCount()) return "The code is expired.";
		inviter->setAvailableCount(inviter->getAvailableCount()-1);
		inviter->addCredit(10);
		plus10=true;
	}	

	for(int i=0;i<passengers.size();i++){
		if(passengers[i]->getName()==userName) return (userName+" already exists.");
		if(passengers[i]->getPhone()==atol(phone.c_str())) return (phone+" already exists.");
	}

	passengers.push_back(new Passenger(userName,password,atol(phone.c_str()),calendar));
	
	if(plus10) passengers.back()->addCredit(10);
	
	return "";
}

string Server::registerDriver(const vector<string>& args){
	for(int i=0;i<drivers.size();i++){
		if(drivers[i]->getName()==args[0]) 
			return (args[0]+" already exists.");
		if(drivers[i]->getSpaceShip().getNumber()==atol(args[3].c_str())) 
			return (args[3]+" already exists.");
	}	
	try{
		drivers.push_back(new Driver(args[0],args[2],atol(args[3].c_str()),args[4],args[5],args[6],args.size()==8,calendar));
	}catch(ModelNotFound ex){
		return (args[4]+" model not found.");
	}
	return "";
}

string Server::acceptRejectRegistration(std::string driverUserName,bool accept){
	int i;
	bool found=false;
	for (i = 0; i < drivers.size(); i++){
		if(drivers[i]->getName()==driverUserName){
			found=true;
			break;
		}
	}
	if(!found)
		return driverUserName+" does not exists.";
	if((drivers[i]->accepted&&accept))
		return  driverUserName+ " has already accepted "+driverUserName;
	drivers[i]->accepted=accept;
	if(!accept) 
		drivers.erase(drivers.begin()+i);
	return "";

} 
string Server::showRegistrationRequests(){
	string result;
	for (int i = 0; i < drivers.size(); i++){
		if(!drivers[i]->accepted){
			if(result.size()!=0) result.push_back('\n');
			result+=drivers[i]->getName()+" "+ntoa(drivers[i]->getSpaceShip().getNumber())+" "+
			" "+drivers[i]->getSpaceShip().getModel()+" "+drivers[i]->getSpaceShip().getProductYear()+" "+drivers[i]->getSpaceShip().getColor();
			if(drivers[i]->VIP) result+=" VIP";
		}
	}
	return result;
}
string Server::getDiscountCode(Passenger* passenger ){

	if (passenger->getAvailableCount()==0) passenger->setAvailableCount(5); 
	return ntoa((long)passenger)+' '+ntoa(passenger->getAvailableCount());

}

std::string Server::login(string UserName,string pass){

	for (int i = 0; i < loggedInUsers.size(); i++){
		if(loggedInUsers[i]->getName()==UserName)
			return UserName+" has already logged in.";
	}

	for (int i = 0; i < passengers.size(); i++){
		if (passengers[i]->getName()==UserName&&
			passengers[i]->isPasswordCorrect(pass)){

			loggedInUsers.push_back(passengers[i]);
			return "";
		}
	}

	for (int i = 0; i < drivers.size(); i++){
		if (drivers[i]->getName()==UserName&&
			drivers[i]->isPasswordCorrect(pass)){
			if(drivers[i]->accepted==false) return (UserName+"'s registeration is under inspection.");
			loggedInUsers.push_back(drivers[i]);
			return "";
		}
	}

	if(UserName=="admin"&&admin.isPasswordCorrect(pass)){
		
		loggedInUsers.push_back(&admin);
		return "";
	}

	return "Invalid username or password.";
}

std::string Server::logout(User* user){

	for (int i = 0; i < loggedInUsers.size(); i++){
		if(loggedInUsers[i]==user){
			loggedInUsers.erase(loggedInUsers.begin()+i);
			return "";
		}
	}
	return "Won't happen";
}

string 	Server::setStatus(Driver* driver,string state,string address){
		
	if(state!="available"&&state!="unavailable")
		return "Invalid state.";
	if(state=="available"&&address=="")
		return "Address should be specified.";
	if(driver->getStatus()=="triping")
		return driver->getName()+" can't change address till trip ends.";
	driver->setStatus(state);
	if(address!=""){
		try{
			driver->setAddress(address);
		}catch(BadAddress ex){
			return "Invalid address.";
		}
	}
	return "";
}

std::string Server::estimateTrip(const std::vector<string>& command){
	Passenger* currentPassenger=findPassenger(command[0]);
	int init= command[2]=="VIP" ? 3 : 2;
	int distance=0;
	try{
		for (int i = init; i < command.size()-1; i++)
			distance+=Address(command[i]).distanceWith(Address(command[i+1]));
	}catch(BadAddress ex){
		return "Invalid address.";
	}
	double coefcient=1;
	if(command[2]=="VIP") coefcient=2;
	if(currentPassenger->isJournier(&calendar)) coefcient=0.5;
		return ntoa(distance)+' '+ntoa(coefcient*distance);
}

std::string Server::requestTrip(const std::vector<string>& command){

	Passenger* currentPassenger=findPassenger(command[0]);

	if(!currentPassenger) return command[0] +" does not exists.";
	int init= command[2]=="VIP" ? 3 : 2;

	if(currentPassenger->getLastTrip()&& !currentPassenger->getLastTrip()->done)
		return "Last trip is still undone.";

	if(currentPassenger->getLastTrip()&& !currentPassenger->getLastTrip()->getRate())
		return "Last trip is not rated.";

	Trip* newTrip=new Trip(calendar,currentPassenger,command[2]=="VIP");
	try{
		for (int i = init; i < command.size(); i++)
			newTrip->addLandmark(Address(command[i]));
	}catch(BadAddress ex){
		return "Invalid address.";
	}
	newTrip->setCost();
	if(newTrip->getPassenger()->getCredit()-newTrip->getCost()<-10){
		delete newTrip;
		return newTrip->getPassenger()->getName()+" doesn't have enought credit.";
	}
	
	if(!addToDriversRequests(newTrip)){
		delete newTrip;
		return "No driver is available at the moment.";
	}
	currentPassenger->addTrip(newTrip);

	return ntoa(newTrip->getCost())+" "+ntoa(newTrip->distance());
}

class wayToSort {
public:
    wayToSort(Trip* trip) : trip(trip) {}
    bool operator()(Driver* a,Driver* b) {
 
    	if(a->getStatus()=="available"&&b->getStatus()!="available") return true;
    	if(a->getStatus()!="available"&&b->getStatus()=="available") return false;
    	
    	if(trip->VIP){
    		if(a->VIP&&!b->VIP) return true;
    		if(!a->VIP&&b->VIP) return false;
    	}

    	if(!trip->VIP){
    		if(a->VIP&&!b->VIP) return false;
    		if(!a->VIP&&b->VIP) return true;
    	}

    	return -a->getRate()+(trip->getSource().distanceWith(a->getAddress())) <
    	-b->getRate()+(trip->getSource().distanceWith(b->getAddress()));
    }
private:
    Trip* trip;
};
bool Server::addToDriversRequests(Trip* trip){

	sort(drivers.begin(),drivers.end(),wayToSort(trip));

	bool anyExists=false;
	int numOfCapableUsers=0;
	for (int i = 0; i < drivers.size(); i++){
		if(numOfCapableUsers>=4) 
			break;
		if(drivers[i]->getStatus()!="available")
			break;
		if((!trip->VIP&&drivers[i]->VIP)||(trip->VIP&&!drivers[i]->VIP))
			break;
		drivers[i]->addRequest(trip);
		numOfCapableUsers++;
		anyExists=true;
	}
	return anyExists;
}

void Server::removeFromDriversRequests(Trip* trip){

	for (int i = 0; i < drivers.size(); i++)
		drivers[i]->removeRequest(trip);
}

string Server::cancelTrip(Passenger* passenger){

	if(!passenger->getLastTrip()) return "";
	if(passenger->getLastTrip()->getDriver())
		return "Your trip request is accepted, you can not cancel the trip.";
	
	removeFromDriversRequests(passenger->getLastTrip());
	delete passenger->getLastTrip();
	passenger->removeLastTrip();
	return "";
}
string Server::showTripRequests(Driver* driver){

	string result;
	std::vector<Trip*> requests=driver->getRequests();
	
	for (int i = 0; i < requests.size(); i++){
		if(result!="") result+='\n';
		result+=requests[i]->getPassenger()->getName()+' '+requests[i]->getLandmarks()+
		' '+ntoa(requests[i]->getCost())+' '+ntoa(requests[i]->distance());
	}

	return result;
}

string Server::acceptTripRequest(Driver* driver,string passengerUserName){
	
	std::vector<Trip*> requests=driver->getRequests();
	
	for (int i = 0; i < requests.size(); ++i){
		if(requests[i]->getPassenger()->getName()==passengerUserName){
			driver->addToTrips(requests[i]);
			driver->setStatus("triping");
			requests[i]->setDriver(driver);
			removeFromDriversRequests(requests[i]);
			return "";
		}
	}
	return passengerUserName+"'s trip was not found.";
}

string Server::tripStatus(Passenger* passenger){
	
	Trip* lastTrip=passenger->getLastTrip();
	if(!lastTrip||lastTrip->done) 
		return passenger->getName()+" doesn't have undone trip.";

	Driver* tripDriver=lastTrip->getDriver();
	if(!tripDriver)
		return "waiting";
	SpaceShip driverSpaceShip=tripDriver->getSpaceShip();

	return "accepted "+tripDriver->getName()+" "+tripDriver->getAddress().toStr()+" "+
	driverSpaceShip.getModel()+" "+driverSpaceShip.getColor();
}

string Server::setTime(std::string newDate){
	
	if(DateTime(newDate)<calendar)
		return "Can't set time to the past.";
	if(DateTime(newDate).differInDate(calendar)){
		for (int i = 0; i < drivers.size(); ++i){
			int salary=drivers[i]->calcSalary();
			drivers[i]->addCredit(0.8*salary);
			credit-=0.8*salary;
		}
	}
	calendar=DateTime(newDate);
	return "";
}
string Server::driverReport(string userName,string beginingDate,string endDate){
	int tripCount=0;int totalIncome=0;int totalRate=0;
	DateTime begin(beginingDate);
	DateTime end(endDate);
	for (int i = 0; i < drivers.size(); ++i){
		std::vector<Trip*> driverTrips=drivers[i]->getTrips();
		for (int j = 0; j < driverTrips.size(); ++j){
			if(begin<driverTrips[j]->getDate()&&driverTrips[j]->getDate()<end){
				tripCount++;
				totalIncome+=driverTrips[j]->getCost();
				totalRate+=driverTrips[j]->getRate();
			}
		}
	}
	return ntoa(tripCount)+" "+ntoa(totalIncome)+" "+ntoa(totalRate);
}

string Server::passengerReport(std::string userName){
	for (int i = 0; i < passengers.size(); ++i){
		if(passengers[i]->getName()==userName)
			return ntoa(passengers[i]->getCredit());
	}
	return userName +" does not exists.";
}

string Server::systemReport(string beginingDate,string endDate){
	
	int systemCredit=0;int driversCount=0;int tripCount=0;int passengersCount=0;
	
	DateTime begin(beginingDate);
	DateTime end(endDate); 
	
	for (int i = 0; i < drivers.size(); ++i){
		
		if(begin<drivers[i]->getRegistrationDate()&&drivers[i]->getRegistrationDate()<end)
			driversCount++;
		
		std::vector<Trip*> driverTrips=drivers[i]->getTrips();
		for (int  j= 0; j < driverTrips.size(); ++j){
			if(begin<driverTrips[j]->getDate()&&driverTrips[j]->getDate()<end){
				tripCount++;
				systemCredit+=driverTrips[j]->getCost();
			}
		}
	}

	for (int i = 0; i < passengers.size(); ++i)
		if(begin<passengers[i]->getRegistrationDate()&&passengers[i]->getRegistrationDate()<end)
			passengersCount++;

	return ntoa(systemCredit)+" "+ntoa(tripCount)+" "+ntoa(driversCount)+" "+ntoa(passengersCount);
}


Server::~Server(){
	
	for (int i = 0; i < drivers.size(); ++i){
		delete drivers[i];
	}
	
	for (int i = 0; i < passengers.size(); ++i){
		delete passengers[i];
	}
}