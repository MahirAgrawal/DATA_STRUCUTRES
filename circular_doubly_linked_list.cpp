#include<iostream>
#include<stdio.h>
template<class X>
class cdlist;
template<class X>
class node{
node *previous = NULL;
node *next = NULL;
X data;
public:
node()
{
previous = NULL;
next = NULL;
}
~node()
{
previous = NULL;
next = NULL;
}
friend class cdlist<X>;
};
template<class X>
class cdlist{
node<X> *head = NULL;
node<X> *tail = NULL;
node<X> *spare = NULL;
int index = 0;
cdlist()
{
head = NULL;
tail = NULL;
index = 0;
}
~cdlist()
{
if(head == NULL){cout<<"INSIDE IF"<<endl;}
else if(head == tail)
	{
	delete head;
	cout<<"INSIDE ELSE IF WHICH IS ONE NODE ONLY"<<endl;
	}
else{
do{
spare = head;
tail = head -> next; 
delete spare;
}while(spare != head);  }
head = NULL;
tail = NULL;
}
int size()
{
return index;
}
void atfirst(X& d)
{
head = new node<X>;
head -> data = d;
head -> next = head;
head -> previous = head;
tail = head;
}
void push_back(X& d)
{
if(head == NULL)
	atfirst(d);
else{
node<X> *ptr = new node<X>;
ptr -> data = d;
ptr -> next = head;
head -> previous = ptr;
ptr -> previous = tail;
tail -> next = ptr;
tail = ptr;
}
index++;}
void push_front(X& d)
{
if(head == NULL)
	atfirsrt(d);
else{
node<X> *ptr = new node<X>;
ptr -> data = d;
ptr -> previous = tail;
tail -> next = ptr;
ptr -> next = head;
head -> previous = ptr;
head = ptr;
}
index++;}
};
