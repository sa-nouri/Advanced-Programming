#ifndef READING_FILE_ERR_H
#define READING_FILE_ERR_H
#include <string>
class readingFileErr{
public:
	readingFileErr(std::string );
	std::string getFileName();
private:
	std::string fileName;	
};
#endif