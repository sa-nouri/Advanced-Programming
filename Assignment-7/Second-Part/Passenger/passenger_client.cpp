#include "passenger_client.h"
using namespace std;

PassengerClient::PassengerClient(std::string serverAddress,int serverPort)
:socket(serverAddress,serverPort){
	userName="";
}

vector<string> PassengerClient::parseCommand(string cmd){
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

std::string PassengerClient::sendRequest(std::string cmd){
	
	vector<string> commandArgs=parseCommand(cmd);
	int numOfArgs=commandArgs.size();
	
	if(commandArgs[0]=="login"){
		if(numOfArgs!=3)
			return "Bad arguments.";
		return  login(commandArgs[1],commandArgs[2]);
	}

	if(commandArgs[0]=="register"){
		if(numOfArgs==4)
			return registerPassenger(commandArgs[1],commandArgs[2],commandArgs[3],"");
		else if(numOfArgs==5)
			return registerPassenger(commandArgs[1],commandArgs[2],commandArgs[3],commandArgs[4]);
		else
			return "Bad arguments.";
	}
	
	//By then user must be registered.
	if(userName=="")
		return "Please first register of login.";

	if(commandArgs[0]=="logout"){
		if(numOfArgs!=1)
			return "Bad arguments.3";
		return logout();
	}
	if(commandArgs[0]=="get_discount_code"){
		if(numOfArgs !=1)
			return "Bad arguments.4";
		return stickUserName(cmd);
	}	
	if(commandArgs[0]=="estimate_trip"||commandArgs[0]=="request_trip"){
		if(numOfArgs <4)
			return "Bad arguments.5";
		return stickUserName(cmd);
	}
	if(commandArgs[0]=="cancel_trip_request"){
		if(numOfArgs !=1)
			return "Bad arguments.6";
		return stickUserName(cmd);
	}
	if(commandArgs[0]=="trip_status"){
		if(numOfArgs !=1)
			return "Bad arguments.7";
		return stickUserName(cmd);
	}
	if(commandArgs[0]=="rate_driver"){
		if(numOfArgs !=2)
			return "Bad arguments.8";
		return stickUserName(cmd);
	}
	if(commandArgs[0]=="charge_account"){
		if(numOfArgs !=2)
			return "Bad arguments.9";
		return stickUserName(cmd);
	}
	return "Unknown command entered.";
}	

std::string PassengerClient::login(string _userName,string password){
			
	socket.send(_userName+" login "+password);
	string response=socket.receive();

	if(response=="") 
		userName=_userName;
	return response;
}
std::string PassengerClient::logout(){

	socket.send(userName+" logout");
	userName="";
	return socket.receive();
}
std::string PassengerClient::registerPassenger(string _userName,
	string password,string phone,string discountCode){
	string diccountArg=discountCode=="" ? "" : " "+discountCode;
	socket.send(_userName+" register_passenger "+password+" "+phone+diccountArg);
	return socket.receive();
}
std::string PassengerClient::stickUserName(string cmd){
	
	socket.send(userName+" "+cmd);
	return socket.receive();
}
