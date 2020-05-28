#include<cstdio>
#include<iostream>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
template<class X>
class doubly_list;
template<class X>
class node{
node *previous = NULL;
X data;
node *next = NULL;
public:
node()
{
next = NULL;
previous = NULL;
}
~node()
{
next = NULL;
previous = NULL;
}
friend class doubly_list<X>;
};
template<class X>
class doubly_list{
node<X>* head = NULL;
node<X>* tail = NULL;
int index = 0;
public:
linked_list()
{
head = NULL;
tail = NULL;
}
void atfirst(X& d)
{
head = new node<X>;
head -> data = d;
head -> next = NULL;
head -> previous = NULL;
tail = head;
index++;
}
void push_back(X& d)
{
if(head == NULL)
	atfirst(d);
else{
node<X>*ptr =  new node<X>;
ptr -> next = NULL;
ptr -> data = d;
tail -> next = ptr;
ptr -> previous = tail;
tail = ptr;
index++;}
}
void push_front(X& d)
{
if(head == NULL)
	atfirst(d);
else{  
node<X>*ptr =  new node<X>;
ptr -> previous = NULL;
ptr -> data = d;
ptr -> next = head;
head -> previous = ptr;
head = ptr; 
index++;}
}
void push(int i,X& d)
{
if(i < 0)
	return;
else if(i == 0)
	push_front(d);
else if(i >= index)
	push_back(d);
else{
node<X>* ptr = head;
for(int j = 0;j < i-1;j++)
	ptr = ptr -> next;
node<X>* new_ptr = new node<X>;
new_ptr -> data = d;
new_ptr -> previous = ptr;
node<X>* temp_ptr = ptr -> next;
ptr -> next = new_ptr;
ptr = temp_ptr;
ptr -> previous = new_ptr;
new_ptr -> next = ptr;
index++;}
}
void pop_back()
{
if(head == NULL)
	return;
else if(head -> next == NULL)
	{
	delete head;
	head = NULL;
	tail = NULL;
	return;
	}
node<X>* ptr = tail;
tail = tail -> previous;
tail -> next = NULL;
delete ptr;
index--;}
void pop_front()
{
if(head == NULL)
	return;
else if(head -> next == NULL)
	{
	delete head;
	head = NULL;
	tail = NULL;
	return;
	}
node<X>* ptr = head;
head = head -> next;
head -> previous = NULL;
delete ptr;
index--;}
void pop(int i)
{
if(i < 0 || i >= index)
	return;
else if(i == 0)
	pop_front();
else if(i == (index-1))
	pop_back();
else{
node<X>* ptr = head;
for(int j = 0;j < i-1;j++)
	ptr = ptr -> next;
node<X>* ptr2 = ptr -> next;
node<X>* ptr3 = ptr2 -> next;
ptr -> next = ptr3;
ptr3 -> previous = ptr;
delete ptr2;
}
index--;
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
void display()
{
if(head == NULL && tail == NULL)
	cout<<"EMPTY!!";
node<X>* ptr = head;
while(ptr != NULL)
{cout<<(ptr -> data)<<" ";
ptr = ptr -> next;}
cout<<endl;
}
void reverse()
{
if(head == tail)
	return;
auto ptr = head;
auto temp = head;
while(ptr != tail)
{
temp = ptr -> previous;
ptr -> previous = ptr -> next;
ptr -> next = temp;
ptr = ptr -> previous;
}
temp = ptr -> previous;
ptr -> previous = ptr -> next;
ptr -> next = temp;
tail = head;
head = ptr;
}
void reverse_display()
{
node<X>* ptr = tail;
while(ptr != NULL)
{cout<<(ptr -> data)<<" ";
ptr = ptr -> previous;}
cout<<endl;
}
};
int main()
{
int a = 9;
doubly_list<int> l;
l.push_back(a);
l.display();
a = 7;
l.push_back(a);
l.display();
l.push_back(a);
l.display();
l.push_front(a);
l.display();
l.push_front(a);
l.display();
l.push_front(a);
l.display();
a = 12;
l.push(0,a);
l.display();
a = 44;
l.push(1,a);
l.display();
l.pop_front();
l.display();
l.pop_back();
l.display();
l.pop(3);
l.display();
l.pop(2);
l.display();
cout<<"REVERSE:"<<endl;
l.reverse_display();
cout<<l.size();
l.pop_back();
l.display();
l.pop_back();
l.display();
l.pop_back();
l.display();
l.pop(3);
l.display();
l.pop(2);
l.display();
l.pop_back();
l.display();
l.pop_back();
l.display();
l.push_front(a);
l.display();
a = 54;
l.push_front(a);
l.display();
a = 50;
l.push_front(a);
l.display();
l.reverse();
l.display();
l.pop_back();
l.display();
l.pop_back();
l.display();
l.reverse();
l.display();
l.pop_back();
l.display();
l.reverse();
l.display();
return 0;
}
