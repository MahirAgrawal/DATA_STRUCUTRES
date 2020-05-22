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
};
void pop_back()
{

}
int main()
{
void display()
{
cout<<"DATA:"<<data<<":"<<(unsigned int)&(this->data)<<endl;
printf("PTR:%u\n",ptr);
}
void display()
{
cout<<"HEAD:"<<head<<endl;
n.display();
}
node<char>n;
n.data = 'c';
n.ptr = &(n.data);
n.display();
list<char>l;
l.head = 'g';
l.n.data = 'f';
l.n.ptr = &(l.n.data);
l.display();
node<int> *ptr = new node<int>;
ptr -> data = 34;
ptr -> ptr = &(ptr -> data);
ptr -> display();
return 0;
}
