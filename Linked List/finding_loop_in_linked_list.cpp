#include<iostream>
#include<stdio.h>
#include<set>
using namespace std;
namespace method1{
class node{
public:
short int index = 0;
int data = 0;
node *next = NULL;
static short int i;
node()
{
index = i;
data = 0;
next = NULL;
i++;
}
};
short int node::i = 0;
int check_loop(node *ptr)
{
short int j = 0;
bool flag = false;
while(1)
{
if(ptr == NULL)
	{
	cout<<"RETURNING\n";
	return -1;
	}
else{
	if((ptr -> index) == j)
	  {
	  j++;
 	  ptr = ptr -> next;
	  }
	else
	  flag = true;
}
if(flag)
	break;
}
return (ptr -> index);
}}
//using namespace method1;
namespace method2{
class node{
public:
bool visited = 0; //HERE LIES THE MAGIC VARIABLE
int data = 0;
node *next = NULL;
node()
{
visited = false;
data = 0;
next = NULL;
}};
//checking the loop by checking stored index in node itself
//checking the loop by checking bool visited int which the node again stores extra bit of information which is bool variable visited. The default value for visited is false. For every traverse we turn visited = true and so if there is loop then we expect that we should come across a node in which already the 'visited' variable is true. If that is a case then we can say we have found there is loop.
node* check_loop(node *ptr)
{
bool flag = false;
while(1)
{
if(ptr == NULL)
	{
	cout<<"RETURNING\n";
	return NULL;
	}
else{
	if((ptr -> visited) == false)
	  {
	  ptr -> visited = true;
 	  ptr = ptr -> next;
	  }
	else
	  flag = true;
}
if(flag)
	break;
}
return (ptr);
}}
//using namespace method2;
namespace method3{
class node{
public:
int data = 0;
node *next = NULL;
node()
{
data = 0;
next = NULL;
}};
//THIS method stores address of already visited nodes and also before any new node checks if the node address existed or not. If existed then surely we have revisited the node due to loop and hence we should stop.
node* check_loop(node *ptr)
{
bool flag = false;
std::set<node*> s;
while(1)
{
if(ptr == NULL)
	{
	cout<<"RETURNING\n";
	return NULL;
	}
else{
	auto it = s.find(ptr);
	if(it == s.end())
	  {
	  s.insert(ptr);
 	  ptr = ptr -> next;
	  }
	else
	  flag = true;
    }
if(flag)
	break;
}
//for(auto it = s.begin();it != s.end();++it)
//	cout<<*(it)<<" ";
return (ptr);}
}
//using namespace method3;
namespace method4{
class node{
public:
int data = 0;
node *next = NULL;
node()
{
data = 0;
next = NULL;
}};
node* check_loop(node *ptr)
{
if(ptr == NULL)
	{
	cout<<"RETURNING\n";
	return NULL;
	}
node *tortoise = ptr;
node *hare = ptr;
bool flag = false;
while(1)
{
if(hare -> next == NULL)
	flag = true;
else if((hare -> next) -> next == NULL)
	flag = true;
else{
hare = (hare -> next) -> next;
tortoise = tortoise -> next;
if(tortoise == hare)
	flag = true;
}	
if(flag == true)
	break;
}
//below method in if block returns the start of loop
//method to find the start of loop in linked_list
if(hare == tortoise)
	{
	hare = ptr;
	while(hare != tortoise)
		{
		hare = hare -> next;
		tortoise = tortoise -> next;
		}
	ptr = hare;
	}
//return null as if hare != tortoise then surely some node address is NULL
else 
	ptr = NULL;
return ptr;}
}
using namespace method4;
int main()
{
node *ptr = NULL,*temp = NULL;
node *head = new node;
cout<<head<<" ";
head -> data = 12;
head -> next = new node;
ptr = head -> next;
cout<<ptr<<" ";
ptr -> data = 13;
ptr -> next = new node;
ptr = ptr -> next;
temp = ptr;
cout<<ptr<<" ";
ptr -> data = 14;
ptr -> next = new node;
ptr = ptr -> next;
cout<<ptr<<" ";
ptr -> data = 15;
ptr -> next = NULL;
cout<<"CHECK LOOP: "<<check_loop(head)<<"TEMP: "<<temp<<endl;
}
