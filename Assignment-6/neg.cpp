#include "neg.h"
Neg::Neg(Functor* child){
	children.push_back(child);
}
void Neg::doTheJob(){
	if(!children[0]->done) throw EarlyToDoTheJob();
	result=-1*children[0]->getResult();
	done=true;
}