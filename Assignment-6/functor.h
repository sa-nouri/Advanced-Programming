#ifndef FUNCTOR_H
#define FUNCTOR_H
#include <vector>
class Functor;
class Functor
{
public:
	Functor();
	virtual ~Functor();
	double getResult();
	bool runTracker();
	bool done;
	void undoneChildren();
	void killChildren();
protected:
	std::vector<Functor*> children;
	double result;
	virtual void doTheJob()=0;
};
#endif