#include "integral.h"
/*This trims the digits from left hand and 
remains a zero when no digits are none-zero*/
void Integral::trim(){
	if(digits.size()<=1 || digits[0]!=0)
		return;
	digits.erase(digits.begin());
	trim();
}

Integral::Integral(){
	digits.push_back(0);
}

Integral::Integral(std::string str){
	if(str.size()<=0 || str[0]=='-')
		throw InvalidInitialValue('-');
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

Integral::Integral(int n){
	if(n<0)
		throw InvalidInitialValue('-');
	if(n==0){
		digits.push_back(0);
	}
	while(n>0){
		digits.insert(digits.begin(),n%10);
		n/=10;
	}
	this->trim();
}

bool Integral::operator==(const Integral& number) const{
	if(digits.size()!=number.digits.size())
		return false;
	bool result=true;
	for(int i=0;i<digits.size();i++){
		if(digits[i]!=number.digits[i])
			result=false;
	}
	return result;
}

bool Integral::operator<(const Integral& rightHand)const{

	if(digits.size()!=rightHand.digits.size())
		return digits.size()<rightHand.digits.size();
	for(int i=0;i<digits.size();i++){
		if(digits[i]!=rightHand.digits[i])
			return digits[i]<rightHand.digits[i];
	}
	return false;
}

Integral Integral::operator+(const Integral& rightHand)const{
	Integral result;
	result.digits.pop_back();
	int carry=0;
	int maxSize=std::max(digits.size(),rightHand.digits.size());
	for(int i=0;i<maxSize;i++){
		int myCurrentIndex=digits.size()-1-i;
		int rightCurrentIndex=rightHand.digits.size()-1-i;
		int myCurrentDigit= myCurrentIndex<0 ? 0 : digits[myCurrentIndex];
		int rightCurrentDigit= rightCurrentIndex<0 ? 0 : rightHand.digits[rightCurrentIndex];
		//std::cerr<<"rCD-myCD:"<<rightCurrentDigit<<'-'<<myCurrentDigit<<std::endl;
		int resultCurrentDigit=rightCurrentDigit+myCurrentDigit+carry;
		carry=resultCurrentDigit/10;
		resultCurrentDigit%=10;
		result.digits.insert(result.digits.begin(),resultCurrentDigit);
	}
	if(carry)
		result.digits.insert(result.digits.begin(),carry);
	if(result.digits.size()==0)
		result.digits.push_back(0); 
	result.trim();
	return result;
}
Integral Integral::diff(const Integral& arg) const{
	if(*this<arg)
		return arg.diff(*this);

	Integral result;
	result.digits.pop_back();
	int carry=0;
	int maxI=std::max(digits.size(),arg.digits.size());
	for(int i=0;i<maxI;i++){
		int myCurrentIndex=digits.size()-1-i;
		int rightCurrentIndex=arg.digits.size()-1-i;
		int myCurrentDigit= myCurrentIndex<0 ? 0 : digits[myCurrentIndex];
		int rightCurrentDigit= rightCurrentIndex<0 ? 0 : arg.digits[rightCurrentIndex];
		int resultCurrentDigit=myCurrentDigit-rightCurrentDigit+carry;
		carry=resultCurrentDigit<0 ? -1 : 0;
		resultCurrentDigit=(resultCurrentDigit+10)%10;
		result.digits.insert(result.digits.begin(),resultCurrentDigit);
	}
	if(result.digits.size()==0)
		result.digits.push_back(0); 
	result.trim();
	return result;
}

Integral::proxy Integral::operator[](int const idx){
	int index=digits.size()-1-idx;
	if (0<=index&&index<digits.size()) 
		return proxy(digits,digits[index],index); 
	else 
		return proxy(digits,0,index);
}

int Integral::operator[](int const idx)const{
	int index=digits.size()-1-idx;
	if (0<=index&&index<digits.size()) 
		return digits[index]; 
	else 
		return 0;
}
Integral::proxy& Integral::proxy::operator=(int const& i){
    if (i >= 0 and i <= 9){
        if(0<=index&&index<subVector.size())
            subVector[index]=i;
        else{
        	int prevSize=subVector.size();
            while(subVector.size()<prevSize-index-1)
                subVector.insert(subVector.begin(),0);
           subVector.insert(subVector.begin(),i);
       }
    value=i;
    while(subVector.size()>1 && subVector[0]==0)
       subVector.erase(subVector.begin());
	}
    else{
            throw InvalidDigitAssignment();
    }
	return *this;
}
Integral::proxy::operator int(){
	return value;
}
std::ostream& operator<<(std::ostream& out,const Integral& number){
	for(int i=0;i<number.digits.size();i++)
    	out << number.digits[i];
    return out;
}