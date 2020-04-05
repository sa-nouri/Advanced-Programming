#ifndef STD_OUT_H
#define STD_OUT_H
#include <iostream>
#include "functor.h"
#include "early_to_do_the_job.h"
class StdOut : public Functor {
public:
	StdOut(Functor* child);
	virtual void doTheJob();
};
#endif