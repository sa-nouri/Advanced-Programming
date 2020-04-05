#include "mul.h"
Mul::Mul(Functor* child1,Functor* child2){
	children.push_back(child1);
	children.push_back(child2);
}
void Mul::doTheJob(){
	if(!children[0]->done||!children[1]->done) throw EarlyToDoTheJob();
	result=children[0]->getResult()*children[1]->getResult();
	done=true;
}