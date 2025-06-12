#ifndef STD_IN_H
#define STD_IN_H
#include <iostream>
#include "functor.h"
#include "early_to_do_the_job.h"
class StdIn : public Functor {
public:
	virtual void doTheJob();
};
#endif