#include <iostream>
#include "big_num.h"
using namespace std;

int main(){
    BigNum n1("123.12");
    BigNum n2(98.12);

    cout<<n1<<" "<<n2<<endl;

    BigNum n3;
    cin>>n3;
    cout<<n3<<endl;

    cout<<n1+n3<<endl;

    cout<<n1[0]<<n1[1]<<n1[2]<<n1[3]<<n1[-1]<<n1[-2]<<n1[-3]<<endl;

    cout<<12+n3<<endl;
    cout<<n3+12<<endl;
    
    return 0;
}
