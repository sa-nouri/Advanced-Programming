#include "std_out.h"
StdOut::StdOut(Functor* child){
	children.push_back(child);
}
void StdOut::doTheJob(){
	if(!children[0]->done) throw EarlyToDoTheJob();
	std::cout<<children[0]->getResult()<<std::endl;
	done=true;
}