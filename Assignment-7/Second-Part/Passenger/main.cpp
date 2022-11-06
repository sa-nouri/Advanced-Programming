#include "client_socket.h"
#include "passenger_client.h"
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "valid operation: " << argv[0] << " [server address] [server port]\n";
    exit(-1);
  }
  try{
      PassengerClient passengerClient(string(argv[1]),Tools::mystoi(argv[2]));
	  string line;
	  while (getline(cin, line)) {
	    if (line == ":q")
	      break;
	    string response=passengerClient.sendRequest(line);
	    cout<<response;
	    if(response!="") cout<<endl;
	  }      
    }catch(NetworkException ex){
      cout<<"Could not establish connecton."<<endl;
      exit(-1);
    }
    
  return 0;
}
