#include "server.h"
using namespace std;
int main(){

	Server server;

	string input;

	while(getline(cin,input)){

		string response= server.getRequest(input);

		cout<<response;

		if(response!="") 
			cout<<endl;
		
	}

}