#include<iostream>
#include<stdio.h>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define MAX_INDEX 50
template<class X>
class stack;
template<class X>
class node{
node *previous;
X data;
node *next;
node()
{
next = NULL;
previous = NULL;
}
~node()
{
next = NULL;
previous = NULL;
//cout<<"NODE WAS DELETED..\n";
}
friend class stack<X>;
};
template<class X>
class stack{
node<X> *head = NULL;
node<X> *current = NULL;
int index = 0;
public:
stack()
{
head = NULL;
current = NULL;
index = 0;
}
void push(X d)
{
if(index >= MAX_INDEX)
	{
	cout<<"STACK OVERFLOW!!!"<<endl;
	return;
	}
node<X> *ptr = new node<X>;
ptr -> data = d;
if(head == NULL)
	{
	ptr -> previous = NULL;
	ptr -> next = NULL;
	head = ptr;
	current = ptr;
	}
else{
current -> next = ptr;
ptr -> previous = current;
ptr -> next = NULL;
current = ptr;
}
index++;
}
void pop()
{
if(head == NULL)
	{
	cout<<"STACK UNDERFLOW!!\n";
	return;
	}	
else{
node<X> *ptr = current -> previous;
delete current;
current = ptr;
if(current == NULL)
	head = NULL;
}
index--;}
X peek()
{
X garbage;
if(current == NULL)
	return garbage;
else
	return (current -> data);
}
int size()
{
return index;
}
bool is_empty()
{
if(head == NULL)
	return true;
else 
	return false;
}
bool is_full()
{
if(index == MAX_INDEX)
	return true;
else
	return false;
}
void clear()
{
if(head == NULL)
	return;
else{
while(head != NULL)
	pop();
}
}
void display()
{
node<X> *ptr = current;
while(ptr != NULL)
	{
	cout<<ptr -> data;
	ptr = ptr -> previous;
	}
cout<<'\n';
}
void reverse()
{
node<X> *ptr = head;
node<X> *temp_store = NULL;
head = current;
current = ptr;
for(int i = 0;i < index;i++)
  {
  temp_store = ptr -> previous;
  ptr -> previous = ptr -> next;
  ptr -> next = temp_store;
  ptr = ptr -> previous;
  }
}
void reverse_display()
{
node<X> *ptr = head;
while(ptr != NULL)
	{
	cout<<ptr -> data;
	ptr = ptr -> next;
	}
cout<<'\n';
}
~stack()
{
clear();
}
};
