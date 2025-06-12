#ifndef INVALID_INITIAL_VALUE_H
#define INVALID_INITIAL_VALUE_H
class InvalidInitialValue{
public:
	InvalidInitialValue(char invalidChar):invalidChar(invalidChar){}
	char getInvalidChar(){return invalidChar;}
private:
	char invalidChar;
};
#endif