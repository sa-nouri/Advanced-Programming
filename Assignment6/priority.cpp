#include "priority.h"

Priority::Priority(){
	srand (time(NULL));
}

void Priority::handle(){
	int totalPriority=0;
	for(int i=0;i<threads.size();i++)
		totalPriority+=threads[i]->getPriority();
	while(threads.size()>0){
		for(int i=0;i<threads.size();i++){
			if(threads[i]->hasCompleted()){
				delete threads[i];
				threads.erase(threads.begin()+i);	
			}else
				if(rand()%threads.size()<threads[i]->getPriority()) 
					threads[i]->doProcess();
		}
	}
}

