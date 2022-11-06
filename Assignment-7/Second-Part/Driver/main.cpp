#include "client_socket.h"
#include "driver_client.h"
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "valid operation: " << argv[0] << " [server address] [server port]\n";
    exit(-1);
  }
  try{
      DriverClient driverClient(string(argv[1]),Tools::mystoi(argv[2]));
	  string line;
	  while (getline(cin, line)) {
	    if (line == ":q")
	      break;
	    string response=driverClient.sendRequest(line);
	    cout<<response;
	    if(response!="") cout<<endl;
	  }      
    }catch(NetworkException ex){
      cout<<"Could not establish connecton."<<endl;
      exit(-1);
    }
    
  return 0;
}
