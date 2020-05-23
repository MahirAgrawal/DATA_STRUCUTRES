#include<cstdio>
#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;
template<class X>
class node{
public:
X data;
node *next = NULL;
node()
{
next = NULL;
}
~node()
{
next = NULL;
cout<<"DATA WAS DELETED!!!";
}
};
template<class X>
class list{
int index = 0;
node<X> *head;
list()
{
index = 0;
head = NULL;
}
void push_back(X value)
{
if(head == NULL)
	{
	head = new node<X>;
	head -> data = value; 
	head -> next = NULL;
	}
else
	{
	node<X> *ptr = head;
	while((ptr->next) != NULL)
		ptr = (ptr -> next);
	(ptr -> next) = new node<X>;
	ptr = ptr -> next;
	ptr -> data = value;
	ptr -> next = NULL;
	}
index++;
}
void push_front(X value)
{
if(head == NULL)
	{
	head = new node<X>;
	head -> data = value; 
	head -> next = NULL;
	}
else{
node<X> *ptr = new node<X>;
ptr -> data = value;
ptr -> next = head;
head = ptr;
}
index++;
}
void pop_back()
{
if(head == NULL)
	return;
node<X> *ptr = head;
for(int i = 0;i < (index-1);i++)
	ptr = ptr -> next;
node<X> *temp = ptr -> next;
ptr -> next = NULL;
delete []temp;
index--;
}
void pop_front()
{
if(head == NULL)
	return;
node<X>* ptr = head;
head = head -> next;
delete []ptr;
index--;
}
int size()
{
return index+1;
}
void display()
{
if(head == NULL)
	return;
node<X> *ptr = head;
cout<<"ELEMENTS: ";
while(ptr != NULL)
	{
	cout<<(ptr -> data)<<" ";
	ptr = ptr -> next;
	}
}

int main()
{
list<char> l;
l.push_back('m');
l.display();
l.push_back('i');
l.display();
l.push_front('b');
l.display();
cout<<"SIZE:"<<l.size();
return 0;
}
