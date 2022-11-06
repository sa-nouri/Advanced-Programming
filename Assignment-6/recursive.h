#ifndef RECURSIVE_H
#define RECURSIVE_H
#include "thread.h"
class Recursive : public Thread {
public:
	Recursive(Functor* _head,std::string _name,int _prority=20);
	virtual void doProcess();
};
#endif