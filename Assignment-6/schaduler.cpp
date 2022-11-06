#include "schaduler.h"
Schaduler::~Schaduler(){}
void Schaduler::addThread(Thread* toAdd){
	threads.push_back(toAdd);
}