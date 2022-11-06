#ifndef DATE_TIME
#define DATE_TIME
#include <string>
#include <stdlib.h>

class DateTime {
public:
	bool operator<(const DateTime&);
	DateTime operator-(const DateTime&);
	DateTime operator+(const DateTime&);
	DateTime (std::string);
	bool differInDate(const DateTime& arg);
	int date;
	int hour;
	int minute;
	int second;

private:
	DateTime(int,int,int,int);
};
#endif