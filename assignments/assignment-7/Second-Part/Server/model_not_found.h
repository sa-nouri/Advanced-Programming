#ifndef MODEL_NOT_FOUND
#define MODEL_NOT_FOUND
#include <string>
class ModelNotFound{
public:
	ModelNotFound(std::string str);
private:
	std::string err;
};
#endif