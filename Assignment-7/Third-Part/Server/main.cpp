#include "taxiare.h"
#include "server.h"
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
  
  if (argc != 2) {
    cerr << "valid operation: " << argv[0] << " [port number]\n";
    exit(-1);
  }
  try{
  Taxiare server(Tools::mystoi(argv[1]));
  server.run();
  }catch(NetworkException ex){
  	cout<<"Could not establish connection."<<endl;
  }
  return 0;
}
