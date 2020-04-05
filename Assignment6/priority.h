#ifndef PRIORITY_H
#define PRIORITY_H
#include "schaduler.h"
#include <stdlib.h>
#include <time.h>
class Priority : public Schaduler {
public:
	Priority();
	virtual void handle(); 
};
#endif