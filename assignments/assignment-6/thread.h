#ifndef THREAD_H
#define THREAD_H
#include "functor.h"
#include "bad_priority_value.h"
#include <string>
class Thread
{
public:
	Thread(Functor* _head,std::string _name,int _priority=20);
	virtual ~Thread();
	virtual void doProcess()=0;
	bool hasCompleted();
	int getPriority();
	Functor* getHead(){return head;};
protected:
	Functor* head;
	int priority;
	bool completed;
	std::string name;
};
#endif
