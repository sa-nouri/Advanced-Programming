#ifndef NEG_H
#define NEG_H
#include "functor.h"
#include "early_to_do_the_job.h"
#include <iostream>
class Neg : public Functor {
public:
	Neg(Functor* child);
	virtual void doTheJob();
};
#endif