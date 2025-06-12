#include "recursive.h"
void Recursive::doProcess(){
	if(head->runTracker()){
		head->undoneChildren();
		head->done=false;
	}
}
Recursive::Recursive(Functor* _head,std::string _name,int _prority)
: Thread(_head,_name,_prority){
}