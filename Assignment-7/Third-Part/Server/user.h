#ifndef USER_H
#define USER_H
#include <string>
class User {
public:
	User(std::string userName,std::string password);
	std::string getName();
	bool isPasswordCorrect(std::string);
protected:
	std::string userName;
	std::string password;
};
#endif
