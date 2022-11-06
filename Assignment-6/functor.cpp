#include "functor.h"

using namespace std;

Functor::Functor(){
	done=false;
	result=0;
}

Functor::~Functor(){
}

double Functor::getResult(){
	return result;
}

bool Functor::runTracker(){
	if(children.size()==0){
		this->doTheJob();
		return true;
	}

	bool allChildrenAreDone=true;

	for(int i=0;i<children.size();i++){
		if(!children[i]->done){
			allChildrenAreDone=false;
			children[i]->runTracker();
			break;
		}
	}

	if(allChildrenAreDone){
		this->doTheJob();
		return true;
	}
	return false;
}

void Functor::undoneChildren(){
	for(int i=0;i<children.size();i++){
		children[i]->done=false;
		children[i]->undoneChildren();
	}
}

void Functor::killChildren(){
	for(int i=0;i<children.size();i++){
		children[i]->killChildren();
		delete children[i];
	}		
}