#include<iostream>
#include<stdio.h>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
template<class X>
class clist;
template<class X>
class node{
X data;
node<X>*  next = NULL;
public:
node()
{
next = NULL;
}
friend class clist<X>;
};
template<class X>
class clist{
node<X>* head = NULL;
node<X>* tail = NULL;
int index = 0;
public:
clist()
{
head = NULL;
tail = NULL;
}
void push_back(X& d)
{
node<X>* ptr = new node<X>;
ptr -> data = d;
if(head == NULL)
{ 
head = ptr;
head -> next = head;
}
else{
tail -> next = ptr;
ptr -> next = head;
}
tail = ptr;
index++;}
void push_front(X& d)
{
node<X>* ptr = new node<X>;
ptr -> data = d;
if(head == NULL)
{ 
ptr -> next = ptr;
tail = ptr;
}
else{
ptr -> next = head;
tail -> next = ptr;
}
head = ptr;
index++;}
void push(int i,X& d)
{
if(i < 0 || i >= index)
  return;
else if(i == 0)
  push_front(d);
else if(i == (index - 1))
  push_back(d);
else{
node<X>* ptr = head;
for(int j = 0;j < (i-1);j++)
	ptr = (ptr -> next);
node<X>* temp = new node<X>;
temp -> data = d;
temp -> next = ptr -> next;
ptr -> next = temp;
}
index++;}
void pop_back()
{
if(head == NULL)
	return;
else if(head == tail)
{
delete head;
head = NULL;
tail = NULL;
}
else{
node<X>* ptr = head;
while((ptr -> next) != tail)
	ptr = ptr -> next;
ptr -> next = head;
delete tail;
tail = ptr;
}
index--;}
void pop_front()
{
if(head == NULL)
	return;
else if(head == tail)
{
delete head;
head = NULL;
tail = NULL;
}
else{
node<X>* ptr = head;
head = (head -> next);
tail -> next = head;
delete ptr;
}
index--;}
void pop(int i = -1)
{
if(i < 0 || i >= index)
	return;
else if(i == 0)
	pop_front();
else if(i == (index - 1))
	pop_back();
else{
node<X>* ptr = head;
for(int j = 0;j < (i-1);j++)
	ptr = (ptr -> next);
node<X>* ptr2 = ptr -> next;
ptr -> next = ((ptr -> next)->next);
delete ptr2;
}
index--;}
int size()
{
return index;
}
void display()
{
node<X>* ptr = head;
if(ptr == NULL)
	return;
do{
cout<<ptr -> data<<" ";
ptr = ptr -> next;
}while(ptr != head);
cout<<endl;
}
};
int main()
{
clist<char> l;
char c = 't';
l.push_back(c);
l.display();
c = 'u';
l.push_front(c);
l.display();
c = 'e';
l.push_back(c);
l.display();
c = 'm';
l.push_front(c);
l.display();
c = 'w';
l.push_back(c);
l.display();
c  = 'p';
l.push_front(c);
l.display();
cout<<"POPPING STARTS FROM HERE"<<endl;
l.pop(1);
l.display();
l.pop(3);
l.display();
l.push(1,c);
l.display();
c = 't';
l.push(2,c);
l.display();
c = 'o';
l.push(1,c);
l.display();
return 0;
}
