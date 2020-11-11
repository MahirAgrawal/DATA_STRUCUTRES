#include<iostream>
#include<stdio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
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
public:
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
spare = head;
do{
tail = spare -> next;
delete spare;
spare = tail;
cout<<"deleted"<<endl;
}while(spare != head);
}
head = NULL;
tail = NULL;
}
bool check_valid(int i)
{
if(i < 0 || i >= index)
	return false;
else
	return true;
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
spare = new node<X>;
spare -> data = d;
spare -> next = head;
head -> previous = spare;
spare -> previous = tail;
tail -> next = spare;
tail = spare;
}
index++;}
void push_front(X& d)
{
if(head == NULL)
	atfirst(d);
else{
spare = new node<X>;
spare -> data = d;
spare -> previous = tail;
tail -> next = spare;
spare -> next = head;
head -> previous = spare;
head = spare;
}
index++;}
void push(int i,X &d)
{
bool ans = check_valid(i);
if(ans == false)
	return;
else{
if(i == 0)
	push_front(d);
else if(i == (index - 1))
	push_back(d);
else{
node<X> *ptr = new node<X>;
ptr -> data = d;
spare = head;
for(int j = 0;j < i;j++)
	spare = spare -> next;
(spare -> previous) -> next = ptr;
ptr -> previous = spare -> previous;
ptr -> next = spare;
spare -> previous = ptr;
index++;
}}
}
void pop_front()
{
if(head == NULL)
	return;
else if(head == tail){
delete head;
head = NULL;
tail = NULL;
}
else{
tail -> next = (head -> next);
(head -> next) -> previous = tail;
delete head;
head = tail -> next;
}
index--;}
void pop_back()
{
if(head == NULL)
	return;
else if(head == tail){
delete head;
head = NULL;
tail = NULL;
}
else{
head -> previous = tail -> previous;
(tail -> previous) -> next = head;
delete tail;
tail = head -> previous;
}
index--;}
void pop(int i = 0)
{
bool ans = check_valid(i);
if(ans == false)
	return;
else{
if(i == 0)
	pop_front();
else if(i == (index - 1))
	pop_back();
else{
spare = head;
	for(int j = 0;j < i;j++)
		spare = spare -> next;
(spare -> previous) -> next = spare -> next;
(spare -> next) -> previous = spare -> previous;
delete spare;
index--;
}}
}
void display()
{
if(head == NULL)
	return;
spare = head;
do{
cout<<spare -> data<<" ";
spare = spare -> next;
}while(spare != head);
cout<<endl;
}
void clear()
{
if(head == NULL){cout<<"INSIDE IF"<<endl;}
else if(head == tail)
	{
	delete head;
	cout<<"INSIDE ELSE IF WHICH IS ONE NODE ONLY"<<endl;
	}
else{
spare = head;
do{
tail = spare -> next;
delete spare;
spare = tail;
cout<<"deleted"<<endl;
}while(spare != head);
}
head = NULL;
tail = NULL;
index = 0;}
void reverse()
{
if(head == NULL || (head == tail))
	return;
node<X> *ptr = head;
do{
spare = ptr -> previous;
ptr -> previous = ptr -> next;
ptr -> next = spare;
ptr = ptr -> previous;
}while(ptr != head);
spare = head;
head = tail;
tail = spare;
}
};
int main()
{
cdlist<int> l;
int a = 89;
l.push_back(a);
l.display();
a = 23;
l.push_front(a);
l.display();
a = 43;
l.push_back(a);
l.display();
a = 63;
l.push_front(a);
l.display();
a = 3;
l.push_back(a);
l.display();
//l.clear();
a = 12;
l.push_front(a);
l.display();cout<<"SIZE: "<<l.size()<<endl;
a = 54;
l.push_back(a);
l.display();cout<<"SIZE: "<<l.size()<<endl;
a = 665;
l.push_front(a);
l.display();cout<<"SIZE: "<<l.size()<<endl;
a = 39;
l.push(2,a);
a = 234;
l.push(4,a);
l.display();
l.pop(4);
l.display();cout<<"SIZE: "<<l.size()<<endl;
l.pop(2);
l.display();cout<<"SIZE: "<<l.size()<<endl;
l.pop_back();
l.display();cout<<"SIZE: "<<l.size()<<endl;
l.pop_front();
l.display();cout<<"SIZE: "<<l.size()<<endl;
l.pop_back();
l.display();cout<<"SIZE: "<<l.size()<<endl;
l.pop_front();
l.display();cout<<"SIZE: "<<l.size()<<endl;
l.reverse();
l.display();
l.clear();
l.reverse();
l.display();
return 0;
}
