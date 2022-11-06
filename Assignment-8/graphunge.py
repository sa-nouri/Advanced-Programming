class Stack:
    def __init__(self):
        self.items=[]

    def push(self,toAdd):
        self.items.append(toAdd)

    def pop(self):
        assert len(self.items) , "Unable to pop,no item is left."
        result=self.items[-1]
        del self.items[-1]
        return result

    def top(self):
        assert len(self.items) , "Unable to top,no item is left."
        return self.items[-1]

    def empty(self):
        return (len(self.items)==0)

class Node:
    def __init__(self,_character,_listOfChildren):
        self.character=_character
        self.listOfChildren=_listOfChildren
    def execute(self,stack,pcd,stringMode):
        #print self.character
        skipNode=False
        nums=[0,1,2,3,4,5,6,7,8,9]
        if(self.character==' '):
            pass
        elif(self.character=='"'):
            stringMode=not(stringMode)
        elif(stringMode):
            stack.push(self.character)
        elif(self.character=='+'):
            a=stack.pop()
            b=stack.pop()
            stack.push(a+b)
        elif(self.character=='-'):
            a=stack.pop()
            b=stack.pop()
            stack.push(a-b)            
        elif(self.character=='*'):
            a=stack.pop()
            b=stack.pop()
            stack.push(a*b)
        elif(self.character=='/'):
            a=stack.pop()
            b=stack.pop()
            stack.push(a/b)   
        elif(self.character=='%'):
            a=stack.pop()
            b=stack.pop()
            stack.push(a%b)
        elif(self.character=='!'):
            a=stack.pop()
            stack.push(not(a))
        elif(self.character=='`'):
            a=stack.pop()
            b=stack.pop()
            stack.push(a>b)
        elif(self.character=='^'):
            pcd=pcd+1
        elif(self.character=='v'):
            pcd=pcd-1
        elif(self.character=='?'):
            from random import randint
            pcd=randint(0,len(self.listOfChildren))
        elif(self.character=='_'):
            a=stack.pop()
            if(not(a)):
                pcd=pcd-1
            else:
                pcd=pcd+1
        elif(self.character==':'):
            a=stack.pop()
            stack.push(a)
            stack.push(a)
        elif(self.character=='\\'):
            a=stack.pop()
            b=stack.pop()
            stack.push(a)
            stack.push(b)
        elif(self.character=='$'):
            stack.pop()
        elif(self.character=='.'):
            print ord(stack.pop())
        elif(self.character==','):
            print chr(stack.pop())
        elif(self.character=='#'):
            skipNode=True
        elif(self.character=='&'):
            data = eval(raw_input("Enter a number:"))
            stack.push(data)
        elif(self.character=='~'):
            data=raw_input("Please enter character:")
            stack.push(ord(data))
        elif(nums.count(self.character)):
                stack.push(self.character)
            
        if(not(len(self.listOfChildren)) or self.character=='@'):
            currentIndex=-1;
        else:
            d=pcd%len(self.listOfChildren)
            currentIndex=self.listOfChildren[d]
        return currentIndex,pcd,stringMode,skipNode
        

def loadNodesFromFile(directory):
    allNodes=[]
    with open(directory) as fp:
        for line in fp:
            line=line.strip()
            line=line.split(' ')
            char=line[0]
            if('0'<=char<='9'):
                char=int(char)
            line=[int(x) for x in line[1:]]
            allNodes.append(Node(char,line))
    return allNodes;



    
pcd=0
stack=Stack()
stringMode=False
skipNode=False
import sys
args= sys.argv
allNodes=loadNodesFromFile(args[1]);

currentIndex=0
while(currentIndex!=-1):
    if(skipNode):
        allNodes[currentIndex].character=' '
    elif(allNodes[currentIndex].character=='g'):
        stack.push(allNodes[stack.pop()].character)
    elif(allNodes[currentIndex].character=='p'):
        x=stack.pop()
        v=stack.pop()
        allNodes[x].character=chr(v)
    elif(allNodes[currentIndex].character=='l'):
        x=stack.pop()
        y=stack.pop()
        allNodes[x].listOfChildren.append(y)
    currentIndex,pcd,stringMode,skipNode = allNodes[currentIndex].execute(stack,pcd,stringMode)
    
    
    
