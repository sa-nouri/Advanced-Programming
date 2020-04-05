#include "parser.h"

Parser::Parser(std::string fileAddress){

	std::string line;
	
	std::ifstream filePtr (fileAddress.c_str());
	
	if (filePtr.is_open()){
		while ( getline (filePtr,line) ){
			wholeText+=line+' ';
		}
		filePtr.close();
	}
	else throw unableToOpen(); 
}

std::string findNextChild(const std::string& wholeText,std::size_t& beginning){
	//Assuming beginning is the beginning of "functor_type". 
	beginning=wholeText.find("functor_type",beginning+12);
	size_t i=0;
	for(i=beginning+12;wholeText[i]==' ' || wholeText[i]==':';i++);
	std::string toExamine=wholeText.substr(i,4);
	if(toExamine=="cout") return "cout";
	if(toExamine.substr(0,2)!="if") return toExamine.substr(0,3);
	return "if";
}


int numOfChildren(std::string type){

	if(type=="cin")
		return 0;
	if(type=="cout"||type=="neg")
		return 1;
	if(type=="add"||type=="mul")
		return 2;
	//if(type=="if")
		return 3;
}
Functor* createNode(std::string type,size_t& beginning,const std::string& wholeText){
	Functor* child1,*child2,*child3;
	std::string child1Type,child2Type,child3Type; 
	switch(numOfChildren(type)){
		
		case 1:
			child1Type=findNextChild(wholeText,beginning);
			child1=createNode(child1Type,beginning,wholeText);
			if(type=="cout") 
				return new StdOut(child1);
			return new Neg(child1);
			break;
		case 2:
			child1Type=findNextChild(wholeText,beginning);
			child1=createNode(child1Type,beginning,wholeText);
			child2Type=findNextChild(wholeText,beginning);
			child2=createNode(child2Type,beginning,wholeText);
			if(type=="mul")
				return new Mul(child1,child2);
			return new Add(child1,child2);
			break;

		case 3:
			child1Type=findNextChild(wholeText,beginning);
			child1=createNode(child1Type,beginning,wholeText);
			child2Type=findNextChild(wholeText,beginning);
			child2=createNode(child2Type,beginning,wholeText);
			child3Type=findNextChild(wholeText,beginning);
			child3=createNode(child3Type,beginning,wholeText);
			return new Cond(child1,child2,child3);
			break;
	}
	return new StdIn();
}

std::vector<Thread*> Parser::parse()const{
	std::vector<Thread*> result;
	size_t beginning=0;
	while(1){
		size_t namePlace=wholeText.find("thread_name",beginning);
		if(namePlace==std::string::npos) break;
		else namePlace+=11;

		for(;wholeText[namePlace]==':'||wholeText[namePlace]==' ';namePlace++);
		std::string threadName;
		for(;wholeText[namePlace]!=','&&wholeText[namePlace]!=' ';namePlace++)
			threadName.push_back(wholeText[namePlace]);

		size_t typePlace=wholeText.find("thread_type",beginning)+11;
		for(;wholeText[typePlace]==':'||wholeText[typePlace]==' ';typePlace++);
		std::string threadType=wholeText.substr(typePlace,12)=="basic_thread" ? 
		"basic_thread":wholeText.substr(typePlace,16) ;

		int priority=20;
		size_t priorityPlace=wholeText.find("thread_priority",beginning);
		if(priorityPlace!=std::string::npos&&priorityPlace-typePlace<30){
			priorityPlace+=15;

			for(;wholeText[priorityPlace]==':'||wholeText[priorityPlace]==' ';priorityPlace++);
			std::string priorityStr;
			for(;wholeText[priorityPlace]!=','&&wholeText[priorityPlace]!=' ';priorityPlace++)
				priorityStr.push_back(wholeText[priorityPlace]);
			
			priority=atoi(priorityStr.c_str());
		}

		Functor* head=createNode(findNextChild(wholeText,beginning),beginning,wholeText);	
		
		if(threadType=="basic_thread")
			result.push_back(new Usual(head,threadName,priority));
		if(threadType=="recurrent_thread")
			result.push_back(new Recursive(head,threadName,priority));
		if(threadType=="singlerun_thread")
			result.push_back(new Monolithic(head,threadName,priority));
	}
	return result;
}

