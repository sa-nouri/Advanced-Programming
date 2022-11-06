#include <iostream>
#include <vector>
using namespace std;

int binary(int number)
{
	if(number==1)
		return 1;
	return number%2+10*binary(number/2);
}

int main()
{
	int n;
	cin>>n;
	vector<int> inputs(n);

	for (int i = 0; i < n; i++)
		cin>>inputs[i];

	for (int i = 0; i < n; i++)
		cout<<binary(inputs[i])<<endl;
}
