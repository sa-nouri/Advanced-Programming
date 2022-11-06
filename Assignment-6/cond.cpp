#include "cond.h"
Cond::Cond(Functor* child1,Functor* child2,Functor* child3){
	children.push_back(child1);
	children.push_back(child2);
	children.push_back(child3);
}
void Cond::doTheJob(){
	if(!children[0]->done||!children[1]->done||!children[2]->done) 
		throw EarlyToDoTheJob();
	result=children[0]->getResult()?children[1]->getResult():children[2]->getResult();
	done=true;
}