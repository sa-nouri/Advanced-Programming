#include "big_num.h"

BigNum::BigNum(std::string number){

	if( number.size()==0 || (number[0]=='-'&&number.size()==1)) 
		throw InvalidInitialValue(' ');
	
	if(number[0]=='-'){
		negetive=true;
		number.erase(number.begin());
	}else
		negetive=false;

	size_t pointIndex=number.find('.');
	if(pointIndex==std::string::npos)
		pointIndex=number.size();
	
	if(pointIndex<number.size()-1){
		fractionalPart=Fractional(number.substr(pointIndex+1));

	if(pointIndex!=0)
		integerPart=Integral(number.substr(0,pointIndex));
	}
}
BigNum::BigNum(double n){

	if(n<0){
		negetive=true;
		n*=-1;
	}else
		negetive=false;

	int intOfDouble=(long)n;
	double dummy;
	double fractionOfDouble=(int)round(fabs(modf(n, &dummy)) * 1e5);
	integerPart=Integral(intOfDouble);
	fractionalPart=Fractional((int)fractionOfDouble);
  
}
BigNum& BigNum::operator=(BigNum other){
	fractionalPart=other.fractionalPart;
	integerPart=other.integerPart;
	negetive=other.negetive;
	return *this;
}
BigNum BigNum::operator-()const{
	BigNum result;
	result.fractionalPart=fractionalPart;
	result.integerPart=integerPart;
	if(integerPart==Integral(0))
		return result;
	result.negetive=!negetive;
	return result;
}
bool BigNum::operator==(const BigNum& number) const{
	return(integerPart==number.integerPart) && (fractionalPart==number.fractionalPart);
}

bool BigNum::operator<(const BigNum& rightHand)const{

	if(negetive && !rightHand.negetive)
		return true;
	if(!negetive && rightHand.negetive)
		return false;

	if(negetive && rightHand.negetive){
		if(integerPart==rightHand.integerPart)
			return rightHand.fractionalPart<fractionalPart;
		else
			return rightHand.integerPart<integerPart;		
	}

	if(integerPart==rightHand.integerPart)
		return fractionalPart<rightHand.fractionalPart;
	else
		return integerPart<rightHand.integerPart;
}

BigNum BigNum::operator+(const BigNum& arg)const{
	BigNum result;
	if((!negetive && !arg.negetive) || (negetive && arg.negetive)){
		result.fractionalPart=fractionalPart+arg.fractionalPart;
		result.integerPart=integerPart+arg.integerPart+
		Integral(result.fractionalPart.getCarryOut());
		result.negetive=negetive;
		return result;
	}
	// |a|>|b|
	if((integerPart==arg.integerPart&&arg.fractionalPart<fractionalPart)
		||arg.integerPart<integerPart){
		result.fractionalPart=fractionalPart-arg.fractionalPart;
		result.integerPart=integerPart.diff(arg.integerPart)
		.diff(Integral(-result.fractionalPart.getCarryOut()));
		result.negetive=negetive;
		return result;
	}else
		return (arg+(*this));
}
BigNum& BigNum::operator+=(const BigNum& c)
{
	*this=(*this)+c;
    return *this;
}
BigNum& BigNum::operator++(){
	(*this)=(*this)+1;
	return *this;
}
BigNum BigNum::operator++(int){
	BigNum result=(*this);
	(*this)=(*this)+1;
	return result;
}

BigNum::proxy BigNum::operator[](int const n){
	if (n>=0) 
		return proxy(&integerPart,integerPart[n],n); 
	else
		return proxy(&fractionalPart,fractionalPart[-n-1],n);
}

int BigNum::operator[](int const n)const{
	if (n>=0) 
		return integerPart[n]; 
	else 
		return fractionalPart[-n-1];
}
BigNum::proxy& BigNum::proxy::operator=(int const& i){
	if(index<0)
		(*((Fractional*)subPart))[-index-1]=i;
	else
		(*((Integral*)subPart))[index]=i;
	value=i;
	return *this;
}

BigNum::proxy::operator int(){
	return value;
}

//_______________________________________________________________________
BigNum operator+(const double r, const BigNum& c){
	return c+r;
}

std::istream& operator>>(std::istream& in,BigNum& number){
	std::string dummy;
	in>>dummy;
	number=BigNum(dummy);
	return in;
}

std::ostream& operator<<(std::ostream& out,const BigNum& number){
	if(number.negetive)
		out<<'-';
	out<<number.integerPart<<number.fractionalPart;
    return out; 
}
