#ifndef USUAL_H
#define USUAL_H
#include "thread.h"
class Usual : public Thread {
public:
	Usual(Functor* _head,std::string _name,int _prority=20);
	virtual void doProcess();
};
#endif