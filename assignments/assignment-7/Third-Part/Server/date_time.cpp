#include "date_time.h"

DateTime::DateTime (std::string arg){

	date=atoi(arg.substr(0,arg.find('-')).c_str());
	arg=arg.substr(arg.find('-')+1);

	hour=atoi(arg.substr(0,arg.find(':')).c_str());
	arg=arg.substr(arg.find(':')+1);	

	minute=atoi(arg.substr(0,arg.find(':')).c_str());
	arg=arg.substr(arg.find(':')+1);

	second=atoi(arg.substr(0,arg.find(':')).c_str());
	arg=arg.substr(arg.find(':')+1);

	if(date<0||hour>24||minute>59||second>59) throw "Bad Date";

}

bool DateTime::operator<(const DateTime& arg){
	if(date!=arg.date)
		return date<arg.date;
	if(hour!=arg.hour)
		return hour<arg.hour;
	if(minute!=arg.minute)
		return minute<arg.minute;	
	if(second!=arg.second)
		return second<arg.second;
	return false;
}

DateTime::DateTime (int d,int h,int m,int s){date=d;hour=h;minute=m;second=s;}
DateTime DateTime::operator-(const DateTime& arg){

	if(second<arg.second){
		minute--;
		second+=60;
	}
	if(minute<arg.minute){
		hour--;
		minute+=60;
	}
	if(hour<arg.hour){
		date--;
		hour+=24;
	}
	return DateTime(date-arg.date,hour-arg.hour,minute-arg.minute,second-arg.second);
}

DateTime DateTime::operator+(const DateTime& arg){
	
	int resultSec=second+arg.second;
	
	int resultMin=minute+arg.minute+resultSec/60;
	resultSec%=60;

	int resultHour=hour+arg.hour+resultMin/60;
	resultMin%=60;

	int resultDate=date+arg.date+resultHour/24;
	resultHour%=24;

	return DateTime(resultDate,resultHour,resultMin,resultSec);
}
bool DateTime::differInDate(const DateTime& arg){

	return (date!=arg.date);
}