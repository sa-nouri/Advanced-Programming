#ifndef RANDOM_H
#define RANDOM_H
#include "schaduler.h"
#include <stdlib.h>
#include <time.h>
class Random : public Schaduler {
public:
	Random();
	virtual void handle(); 
};
#endif