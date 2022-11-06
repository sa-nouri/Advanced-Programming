#include "thread.h"
Thread::Thread(Functor* _head,std::string _name,int _priority){
	name=_name;
	head=_head;
	completed=false;
	if(_priority>20||_priority<0) throw badPriorityValue();
	priority=_priority;
}
Thread::~Thread(){
	head->killChildren();
	delete head;
}
bool Thread::hasCompleted(){
	return completed;
}
int Thread::getPriority(){
	return priority;
}