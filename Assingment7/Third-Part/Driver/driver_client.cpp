#include "driver_client.h"
using namespace std;

DriverClient::DriverClient(std::string serverAddress,int serverPort)
:socket(serverAddress,serverPort){
	userName="";
}

vector<string> DriverClient::parseCommand(string cmd){
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

std::string DriverClient::sendRequest(std::string cmd){
	
	vector<string> commandArgs=parseCommand(cmd);
	int numOfArgs=commandArgs.size();
	
	if(commandArgs[0]=="login"){
		if(numOfArgs!=3)
			return "Bad arguments.";
		return  login(commandArgs[1],commandArgs[2]);
	}

	if(commandArgs[0]=="register"){
		if(numOfArgs==7||numOfArgs==8)
			return registerDriver(commandArgs);
		else 
			return "Bad arguments.";
	}
	
	//By then user must be registered.
	if(userName=="")
		return "Please first register of login.";

	if(commandArgs[0]=="logout"){
		if(numOfArgs!=1)
			return "Bad arguments.";
		return logout();
	}
	if(commandArgs[0]=="show_trip_requests"||
		commandArgs[0]=="arrived"||
		commandArgs[0]=="end_trip"){
		
		if(numOfArgs !=1)
			return "Bad arguments.";
		return stickUserName(cmd);
	}	
	if(commandArgs[0]=="set_status"){
		if(numOfArgs!=3&&numOfArgs!=2)
			return "Bad arguments.";
		return stickUserName(cmd);
	}
	if(commandArgs[0]=="accept_trip_request"){
		if(numOfArgs !=2)
			return "Bad arguments.";
		return stickUserName(cmd);
	}

	return "Unknown command entered.";
}	

std::string DriverClient::login(string _userName,string password){
			
	socket.send(_userName+" login "+password);
	string response=socket.receive();

	if(response=="") 
		userName=_userName;
	return response;
}
std::string DriverClient::logout(){

	socket.send(userName+" logout");
	userName="";
	return socket.receive();
}
std::string DriverClient::registerDriver(std::vector<std::string> args){
	
	string command=args[1]+" register_driver "+args[2]+" "+args[3]+" "+args[4]+" "+args[5]+" "+args[6];
	if(args.size()==8) command+=" "+args[7];
	socket.send(command);
	return socket.receive();

}
std::string DriverClient::stickUserName(string cmd){
	
	socket.send(userName+" "+cmd);
	return socket.receive();
}
