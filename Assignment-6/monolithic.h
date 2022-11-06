#ifndef MONOLITHIC_H
#define MONOLITHIC_H
#include "thread.h"
class Monolithic : public Thread {
public:
	Monolithic(Functor* _head,std::string _name,int _prority=20);
	virtual void doProcess();
};
#endif