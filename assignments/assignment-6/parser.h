#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include "threads_library.h"
#include "unable_to_open.h"
#include "functors_library.h"
class Parser
{
public:
	Parser(std::string fileAddress);
	std::vector<Thread*> parse()const;
private:

	std::string wholeText;
};
#endif