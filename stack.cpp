#include<iostream>
#include<stdio.h>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define MAX_INDEX 10
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
cout<<"NODE WAS DELETED..\n";
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
void push(X& d)
{
if(index > MAX_INDEX)
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
void clear()
{
if(head == NULL)
	return;
else{
node<X> *ptr = NULL;
while(current != NULL)
	{
	ptr = current -> previous;
	delete current;
	current = ptr;
	}
}
index = 0;
head = 	NULL;
current = NULL;
}
void display()
{
node<X> *ptr = current;
while(ptr != NULL)
	{
	cout<<ptr -> data<<" ";
	ptr = ptr -> previous;
	}
cout<<'\n';
}
~stack()
{
clear();
}
};
int main()
{
char c = 'm';
stack<char> s;
s.push(c);
s.display();
c = 'i';
s.push(c);
s.display();
c = 'h';
s.clear();
s.push(c);
s.display();
c = 'i';
s.push(c);
s.display();
c = 'r';
s.push(c);
s.display();
c = 'l';
s.push(c);
s.display();
s.pop();
s.display();
s.pop();
s.display();
s.pop();
s.display();
s.pop();
s.display();
cout<<"after";
cout<<s.peek();
return 0;
}
