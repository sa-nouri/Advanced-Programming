#ifndef SCHADULER_H
#define SCHADULER_H
#include "thread.h"
#include <vector>
class Schaduler{
public:
	void addThread(Thread* );
	virtual ~Schaduler();
	virtual void handle()=0;
protected:
	std::vector<Thread*> threads;
};
#endif