#ifndef ROUND_H
#define ROUND_H
#include "schaduler.h"
class Roundrobin: public Schaduler {
public:
	virtual void handle(); 
};
#endif