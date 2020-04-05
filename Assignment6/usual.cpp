#include "usual.h"
Usual::Usual(Functor* _head,std::string _name,int _prority)
: Thread(_head,_name,_prority){
}
void Usual::doProcess(){
	completed=head->runTracker();
}