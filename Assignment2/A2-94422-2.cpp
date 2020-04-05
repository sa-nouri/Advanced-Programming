//USED LIBLARIES & Definitions:	
	#include <iostream>
	#include <vector>
	using namespace std;
	typedef struct Person{
		int val;
		vector<int> children;
	}Person;

//SIGNITURE OF FUNCTIONS:
	vector<Person> Read_Hierarchy();
	int max_val(int PersonIndex,bool person_exists,const vector<Person>& Hierarchy);

int main()
{
	//Hierarchy[0] is dummy!
	vector<Person> Hierarchy=Read_Hierarchy();
	cout<<max_val(1,true,Hierarchy)<<endl;
	return 0;
}

int max_val(int PersonIndex,bool person_exists,const vector<Person>& Hierarchy)
{
	int result=0;
	if(person_exists)
	{
		result=Hierarchy[PersonIndex].val;
		for(int i=0;i<Hierarchy[PersonIndex].children.size();i++)
			result+=max_val(Hierarchy[PersonIndex].children[i],false,Hierarchy);
	}
	if(!person_exists)
	{
		for(int i=0;i<Hierarchy[PersonIndex].children.size();i++)
			result+=max(max_val(Hierarchy[PersonIndex].children[i],true,Hierarchy),
				max_val(Hierarchy[PersonIndex].children[i],false,Hierarchy));
	}
	return result;
}
vector<Person> Read_Hierarchy()
{
	int NumOfMembers;
	cin>>NumOfMembers;
	vector<Person> persons(NumOfMembers+1);
	for(int eachPerson=1;eachPerson<NumOfMembers+1;eachPerson++)
	{
		cin>>persons[eachPerson].val;
		int NumOfChildren;cin>>NumOfChildren;
		
		for(int i=0;i<NumOfChildren;i++)
		{
			int child;cin>>child;
			persons[eachPerson].children.push_back(child);
		}
	}
	return persons;
}
