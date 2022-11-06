#include "roundrobin.h"
#include <iostream>
void Roundrobin::handle(){
	while(threads.size()>0){
		for(int i=0;i<threads.size();i++){
			if(threads[i]->hasCompleted()){
				delete threads[i];
				threads.erase(threads.begin()+i);	
			}else
				threads[i]->doProcess();
		}
	}
}