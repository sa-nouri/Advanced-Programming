#include "user.h"
using namespace std;

string User::getName(){
	return userName;
}

bool User::isPasswordCorrect(std::string pass){
	return password==pass;
}

User::User(string _userName,string _password){
	userName=_userName;
	password=_password;
}