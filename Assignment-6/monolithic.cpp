#include "monolithic.h"

Monolithic::Monolithic(Functor* _head,std::string _name,int _prority)
: Thread(_head,_name,_prority){
}
void Monolithic::doProcess(){
	while(!head->runTracker());
	completed=true;
}