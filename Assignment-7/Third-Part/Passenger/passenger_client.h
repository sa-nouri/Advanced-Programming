#ifndef PASSENGER_CLIENT
#define PASSENGER_CLIENT
#include <vector>
#include <string>
#include <cstdlib>
#include "client_socket.h"

using namespace std;

class PassengerClient{
public:
	PassengerClient(std::string serverAddress,int serverPort);
	std::string sendRequest(std::string);

private:
	std::string userName;
	ClientSocket socket;
	//**********************************************************
	vector<std::string> parseCommand(std::string cmd);
	std::string login(std::string,std::string);
	std::string logout();
	std::string registerPassenger(std::string,std::string,std::string,std::string);
	std::string stickUserName(std::string);
};
#endif