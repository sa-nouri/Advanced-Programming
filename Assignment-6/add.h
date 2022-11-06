#ifndef ADD_H
#define ADD_H
#include "functor.h"
#include "early_to_do_the_job.h"
class Add : public Functor {
public:
	Add(Functor* child1,Functor* child2);
	virtual void doTheJob();
};
#endif