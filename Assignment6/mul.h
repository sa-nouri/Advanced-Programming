#ifndef MUL_H
#define MUL_H
#include "functor.h"
#include "early_to_do_the_job.h"
class Mul : public Functor {
public:
	Mul(Functor* child1,Functor* child2);
	virtual void doTheJob();
};
#endif