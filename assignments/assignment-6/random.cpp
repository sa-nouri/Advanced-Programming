#include "random.h"
Random::Random(){
	srand (time(NULL));
}

void Random::handle(){
	while(threads.size()>0){
		
		int rndIndex=rand()%threads.size();
		
		threads[rndIndex]->doProcess();

		if(threads[rndIndex]->hasCompleted()){
			delete threads[rndIndex];
			threads.erase(threads.begin()+rndIndex);
		
		}
	}
}