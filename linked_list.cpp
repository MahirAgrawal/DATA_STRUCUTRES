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
cout<<"NODE WAS DELETED!!\n";
}
};
template<class X>
class list{
int index = 0;
node<X> *head;
bool empty = true;
public:
list()
{
index = 0;
head = NULL;
bool empty = true;
}
public:
bool is_empty()
{
return empty;
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
empty = false;
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
empty = false;
}
void pop_back()
{
if(head == NULL)
	return;
node<X> *ptr = head;
if((ptr -> next) == NULL)
	{
	head = NULL;
	delete ptr;
	}
else{
for(int i = 0;i < (index-2);i++)
	ptr = ptr -> next;
node<X> *temp = ptr -> next;
ptr -> next = NULL;
delete temp;}
index--;
}
void pop_front()
{
if(head == NULL)
	return;
node<X>* ptr = head;
head = head -> next;
delete ptr;
index--;
}
void operator +(list &l)
{
node<X>* ptr = l.head;
while(ptr != NULL)
	{
	push_back(ptr -> data);
	ptr = ptr -> next;
	}
}
int size()
{
return index;
}
void clear()
{
while(head != NULL)
	pop_back();
}
X at(int i)
{
if(head == NULL)
	return 0;
if(i >= index || i < 0)
	return 0;
else{
	node<X>* temp = head;
	int count = 0;
	while(count != i)
	{
	temp = temp -> next;
	count++;
	}
return (temp -> data);
}
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
cout<<'\n';
}
};
int main()
{
list<char> l;
l.push_back('m');
l.display();
l.pop_back();
l.display();
cout<<"SIZE:"<<l.size();
l.push_back('i');
l.display();
l.push_front('b');
l.display();
l.pop_front();
l.display();
l.push_back('i');
l.display();
l.push_front('b');
l.display();
l.pop_back();
l.display();
list<char> l2;
cout<<"LIST 2\n";
l2.push_back('i');
l2.display();
l2.push_front('u');
l2.display();
l2.push_front('t');
l2.display();
l2.push_front('r');
l2.display();
cout<<l2.at(4)<<endl;
cout<<l2.at(0)<<endl;
cout<<l2.at(1)<<endl;
l + l2;
l.display();
cout<<"SIZE:"<<l.size();
l.clear();
l.display();
cout<<"SIZE:"<<l.size();
return 0;
}
