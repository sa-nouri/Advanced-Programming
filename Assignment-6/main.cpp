#include "threads_library.h"
#include "functors_library.h"
#include "parser.h"
#include "schadulers_library.h"
#include <vector>
#include <string.h>
int main(int argc, char* argv[]){

	if(argc!=3)
		std::cout<<"Bad args passed."<<std::endl;
	else{
		try{
			Parser pp(argv[1]);
		    std::vector<Thread*> threads= pp.parse();

		    Schaduler* schaduler;
		    if(!strncmp(argv[2],"random",6))
		    	schaduler=new Random();
		    else if(!strncmp(argv[2],"roundrobin",10))
		    	schaduler=new Roundrobin();
		    else if(!strncmp(argv[2],"priority",8))
		    	schaduler=new Priority();
		    else {
		    	std::cout<<"No such schaduler found."<<std::endl;
		    	abort();
		    }

		    for(int i=0;i<threads.size();i++)
		    	schaduler->addThread(threads[i]);
		    
		    schaduler->handle();

		    delete schaduler;
		    
		}catch(unableToOpen ex){
		 std::cout<<"Unable to Access file."<<std::endl;
		}
	}


}