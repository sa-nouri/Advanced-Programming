#ifndef COND_H
#define COND_H
#include "functor.h"
#include "early_to_do_the_job.h"
class Cond : public Functor {
public:
	Cond(Functor* child1,Functor* child2,Functor* child3);
	virtual void doTheJob();
};
#endif