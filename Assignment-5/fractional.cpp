#include "fractional.h"
/*This trims the digits from right hand and 
remains a zero when no digits are none-zero*/
void Fractional::trim(){
	if(digits.size()<=1 || digits.back()!=0)
		return;
	digits.pop_back();
	trim();
}
int Fractional::getCarryOut(){
		return carryOut;
		carryOut=0;
}

Fractional::Fractional(){
	carryOut=0;
	digits.push_back(0);
}

Fractional::Fractional(std::string str){
	if(str.size()<=0 || str[0]=='-')
		throw InvalidInitialValue('-');
	carryOut=0;
	for(int i=0;i<str.size();i++){
		if(str[i]>'9' || str[i]<'0') 
			throw InvalidInitialValue(str[i]);
		std::string temp;
		temp.push_back(str[i]);
		int digit=std::atoi(temp.c_str());
		digits.push_back(digit);
	}
	this->trim();
}
Fractional::Fractional(int n){
	if(n<0)
		throw InvalidInitialValue('-');
	carryOut=0;
	if(n==0){
		digits.push_back(0);
	}
	while(n>0){
		digits.insert(digits.begin(),n%10);
		n/=10;
	}
	this->trim();
}

bool Fractional::operator==(const Fractional& number) const{
	if(digits.size()!=number.digits.size())
		return false;
	bool result=true;
	for(int i=0;i<digits.size();i++){
		if(digits[i]!=number.digits[i])
			result=false;
	}
	return result;
}

bool Fractional::operator<(const Fractional& rightHand)const{
	for(int i=0;i<std::min(digits.size(),rightHand.digits.size());i++){
		if(digits[i]!=rightHand.digits[i])
			return digits[i]<rightHand.digits[i];
	}
	return digits.size()<rightHand.digits.size();
}

Fractional Fractional::operator+(const Fractional& rightHand)const{
	Fractional result;
	result.digits.pop_back();
	int carry=0;
	int maxIndex=std::max(digits.size(),rightHand.digits.size())-1;
	for(int i=maxIndex;i>=0;i--){
		int myCurrentDigit= i>digits.size()-1 ? 0 : digits[i];
		int rightCurrentDigit= i>rightHand.digits.size()-1 ? 0 : rightHand.digits[i];
		int resultCurrentDigit=myCurrentDigit+rightCurrentDigit+carry;
		carry=resultCurrentDigit/10;
		resultCurrentDigit%=10;
		result.digits.insert(result.digits.begin(),resultCurrentDigit);
	}
	if(result.digits.size()==0)
		result.digits.push_back(0);
	result.carryOut=carry;
	result.trim();
	return result;
}
Fractional Fractional::operator-(const Fractional& rightHand)const{
	Fractional result;
	result.digits.pop_back();
	int carry=0;
	int maxIndex=std::max(digits.size(),rightHand.digits.size())-1;
	for(int i=maxIndex;i>=0;i--){
		int myCurrentDigit= i>digits.size()-1 ? 0 : digits[i];
		int rightCurrentDigit= i>rightHand.digits.size()-1 ? 0 : rightHand.digits[i];
		int resultCurrentDigit=myCurrentDigit-rightCurrentDigit+carry;
		carry=resultCurrentDigit<0 ? -1 : 0;
		resultCurrentDigit=(resultCurrentDigit+10)%10;
		result.digits.insert(result.digits.begin(),resultCurrentDigit);
	}
	if(result.digits.size()==0)
		result.digits.push_back(0);
	result.carryOut=carry;
	result.trim();
	return result;	
}

Fractional::proxy Fractional::operator[](int const index){
	if (index<digits.size()) 
		return proxy(digits,digits[index],index); 
	else 
		return proxy(digits,0,index);
};
int Fractional::operator[](int const index)const{
	if (index<digits.size()) return digits[index]; else return 0;
}
Fractional::proxy& Fractional::proxy::operator=(int const& i){
if (i >= 0 and i <= 9){
if(index<subVector.size())
subVector[index]=i;
else{
while(subVector.size()<index)
subVector.push_back(0);
subVector.push_back(i);
}
value=i;
while(subVector.size()>1 && subVector.back()==0)
subVector.pop_back();
}
else{
throw InvalidDigitAssignment();
}
 return *this;
}
Fractional::proxy::operator int(){
    return value;
}

std::ostream& operator<<(std::ostream& out,const Fractional& number){
	if(number.digits.size()==1 && number.digits[0]== 0) 
		return out;
	out<<'.';
	for(int i=0;i<number.digits.size();i++)
    	out << number.digits[i];
    return out;
}
